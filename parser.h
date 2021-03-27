#pragma once
#include <QJsonDocument>
#include <QXmlStreamReader>
#include <QtCharts/QLineSeries>

typedef struct{
    int x;
    int y;
}point;

class Parser{
    public:
        Parser();
        ~Parser();

        int current;
        point *parseFile(char *fileName);

};
