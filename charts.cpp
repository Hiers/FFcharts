#include "charts.h"
#include <stdio.h>
#include <stdlib.h>

Charts::Charts(){
    //dynamic array of series to add and remove at will
    allSeries = (QtCharts::QLineSeries**)malloc(5*sizeof(QtCharts::QLineSeries*));
    chart = new QtCharts::QChart();
    current = 0;
    max = 5;

    xAxis = new QtCharts::QValueAxis();
    vmafAxis = new QtCharts::QValueAxis();
    bitrateAxis = new QtCharts::QValueAxis();
    
    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(vmafAxis, Qt::AlignLeft);
    chart->addAxis(bitrateAxis, Qt::AlignRight);
}

Charts::~Charts(){
    for(int a = 0; a < max; a++)
        delete allSeries[a];
    delete allSeries;
    //chart is already deleted by chartView
}

QtCharts::QChart* Charts::createChart(point *dataSet, int type, int n_subsample){
    allSeries[current] = new QtCharts::QLineSeries();

    for(int a = 1; a < dataSet[0].y; a+=n_subsample){
        allSeries[current]->append(dataSet[a].x, dataSet[a].y);
    }
    
    if(max == current+1)
        allSeries = (QtCharts::QLineSeries**)realloc(allSeries, 2*max);


    chart->addSeries(allSeries[current]);
    allSeries[current]->setName("crf 40");//change this to get the filename. also change parameters to take in filename
    allSeries[current]->attachAxis(xAxis);

    if(xAxis->max() < dataSet[0].y)
        xAxis->setMax(dataSet[0].y);
    if(dataSet[0].x < 0){
        allSeries[current]->attachAxis(bitrateAxis);
    }
    else{
        allSeries[current]->attachAxis(vmafAxis);
    }
    current++;
    return chart;
}

QtCharts::QChart* Charts::removeSeries(int row){
    chart->removeSeries(allSeries[row]);
    printf("%d\n", row);
    delete allSeries[row];
    allSeries[row] = NULL;

    for(int a = row; a < max; a++)
        allSeries[a] = allSeries[a+1];

    current--;
    if(current < max/3)
        allSeries = (QtCharts::QLineSeries**)realloc(allSeries, max/2);
    return chart;
}

