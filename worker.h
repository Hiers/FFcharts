#pragma once
#include <QObject>
#include "parser.h"

class Worker:public QObject{
    Q_OBJECT

    public:
        Worker();

    private:
        Parser *parser;
        int current;

    public slots:
        void parseFile(QString fileName);

    signals:
        void placeholder(point *dataSet);
};
