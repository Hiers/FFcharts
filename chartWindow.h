#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QtCharts/QChart>
#include "customChartView.h"
#include <QtCharts/QLineSeries>

class chartWindow:public QWidget{
    public:
        chartWindow();
        ~chartWindow();
        void changeChart(QtCharts::QChart *chart);
    
    private:
        QPoint mPos;
        QPoint mPrevPos;

        QHBoxLayout *buttons;

        QButtonGroup *exclusiveCheck;
        QPushButton *moveBtn;
        QPushButton *rubberBtn;

        QVBoxLayout *layout;
        customChartView *chartView;
};


