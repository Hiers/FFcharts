#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include "parser.h"
#include <stdlib.h>

Parser::Parser(){
}
Parser::~Parser(){
}

point *Parser::parseFile(char *fileName){
    QFile file(fileName);
    QJsonParseError err;


    if(!file.open(QIODevice::ReadOnly)){
        printf("REALLY file: %s, %s - %d\n", fileName, file.errorString().toUtf8().data(), file.error());
        return NULL;//emit some signal
    }
    else{
        QByteArray text = file.readAll();
        QJsonDocument json = QJsonDocument::fromJson(text, &err);
        point *dataSet = NULL;
        int size;
        int vmaf;
        int bitrate;

        //if file is not valid json, try xml
        if(json.isNull()){
            QXmlStreamReader xml;
            xml.addData(text);

            xml.readNextStartElement();
            while(xml.name() != QLatin1String("frame")){
                xml.readNextStartElement();

                if(xml.name() == QLatin1String("fyi")){
                    size = xml.attributes().value(QStringLiteral("numOfFrames")).toInt();
                    vmaf = xml.attributes().value(QStringLiteral("aggregateVMAF")).toDouble();
                    dataSet[0].x = vmaf;
                    dataSet[0].y = size;
                    xml.skipCurrentElement();
                }
            }

            if(xml.hasError()){
                return NULL;
            }
            free(dataSet);
            dataSet = (point*)malloc(sizeof(point)*(size + 1));
            
            xml.skipCurrentElement();
            xml.readNextStartElement();
            for(int a = 1; a < size; a++){
                dataSet[a].x = xml.attributes().value(QStringLiteral("frameNum")).toInt();
                dataSet[a].y = xml.attributes().value(QStringLiteral("vmaf")).toDouble();
                xml.skipCurrentElement();
                xml.readNextStartElement();
            }

            if(xml.hasError()){
                file.close();
                return NULL;
            }
            file.close();
            return dataSet;
        }
        else{
            if(json["packets"].toArray().isEmpty()){
                QJsonArray frames = json["frames"].toArray();
                //in case a non-ffmpeg vmaf json file gets selected
                if(!frames[0].toObject().contains("metrics")){
                    file.close();
                    return NULL;
                }

                size = (frames.last().toObject()["frameNum"].toInt() /
                    json["params"]["subsample"].toInt());
                vmaf = json["VMAF score"].toDouble();
                
                free(dataSet);
                dataSet = (point*)malloc(sizeof(point)*(size + 1));

                for(int a = 1; frames[a].isObject(); a++){
                    dataSet[a].x = frames[a].toObject()["frameNum"].toInt();
                    dataSet[a].y = frames[a].toObject()["metrics"].toObject()["vmaf"].toDouble();
                }
                dataSet[0].x = vmaf;
                dataSet[0].y = size;
                file.close();
                return dataSet;
            }
            else{
                QJsonArray packets = json["packets"].toArray();
                printf("TAAAAAAAAAAAA\n");
                
                size = packets.size();
                double packet_size;
                bitrate = 0;
                
                free(dataSet);
                dataSet = (point*)malloc(sizeof(point)*(size+1));
                
                for(int a = 1; packets[a].isObject(); a++){
                    packet_size = (packets[a].toObject()["size"].toString().toInt() /
                        packets[a].toObject()["duration_time"].toString().toDouble()) * 8 / 1000;
                    
                    dataSet[a].x = a;
                    dataSet[a].y = packet_size;
                    
                    bitrate += packet_size;
                }
                dataSet[0].x = (bitrate / size) * (-1);
                dataSet[0].y = size;
                printf("%d\n", size);
                
                file.close();
                return dataSet;
                
                
            }
        }

    }
    
}
