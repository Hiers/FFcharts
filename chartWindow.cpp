#include "chartWindow.h"
chartWindow::chartWindow(){
    
    layout = new QVBoxLayout();
    chartView = new QtCharts::QChartView();
    chartView->setVisible(1);

    layout->addWidget(chartView);
    setLayout(layout);
}

chartWindow::~chartWindow(){
    delete layout;
}

void chartWindow::changeChart(QtCharts::QChart *chart){
    chartView->setChart(chart);
}
