#include <iostream>
#include "worker.h"
#include <unistd.h>

Worker::Worker(){
    parser = new Parser();
    current = 0;
}

Worker::~Worker(){
    delete parser;
}


void Worker::parseFile(QString fileName){
    point *dataSet = parser->parseFile(fileName.toUtf8().data());
    if(dataSet){
        emit placeholder(dataSet);
    }
}
