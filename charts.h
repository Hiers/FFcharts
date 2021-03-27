#pragma once
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include "parser.h"

class Charts{

    public:
        Charts();
        QtCharts::QChart *createChart(point *series, int type, int n_subsample);
        QtCharts::QChart* removeSeries(int row);

    private:
        int current;
        int max;
        QtCharts::QLineSeries **allSeries;
        QtCharts::QChart *chart;
};
