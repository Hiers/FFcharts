#include "charts.h"
#include <stdio.h>
#include <stdlib.h>

Charts::Charts(){
    allSeries = (QtCharts::QLineSeries**)malloc(5*sizeof(QtCharts::QLineSeries*));
    current = 0;
    chart = new QtCharts::QChart();
    chart->setTitle("Vmaf chart");
}

QtCharts::QChart* Charts::createChart(point *dataSet, int type, int n_subsample){
    allSeries[current] = new QtCharts::QLineSeries();
    allSeries[current]->setName("crf 40");

    for(int a = 1; a < dataSet[0].y; a+=n_subsample){
        allSeries[current]->append(dataSet[a].x, dataSet[a].y);
    }
                
    chart->addSeries(allSeries[current]);
    chart->createDefaultAxes();
    current++;
    return chart;
}
