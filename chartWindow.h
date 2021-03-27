#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

class chartWindow:public QWidget{
    public:
        chartWindow();
        ~chartWindow();
        void changeChart(QtCharts::QChart *chart);
    
    private:
        QVBoxLayout *layout;
        QtCharts::QChartView *chartView;
};


