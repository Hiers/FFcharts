#include "chartWindow.h"

chartWindow::chartWindow(){
    
    buttons = new QHBoxLayout();
    buttons->insertStretch(0, 1);
    buttons->setSpacing(1);


    moveBtn = new QPushButton("wa");
    rubberBtn = new QPushButton("rub");
    moveBtn->setFixedSize(30, 30);
    rubberBtn->setFixedSize(30, 30);
    moveBtn->setCheckable(true);
    moveBtn->setChecked(true);
    rubberBtn->setCheckable(true);
    
    exclusiveCheck = new QButtonGroup();
    exclusiveCheck->addButton(moveBtn);
    exclusiveCheck->addButton(rubberBtn);
    exclusiveCheck->setId(moveBtn, 0);
    exclusiveCheck->setId(rubberBtn, 1);

    buttons->addWidget(moveBtn);
    buttons->addWidget(rubberBtn);


    layout = new QVBoxLayout();
    chartView = new customChartView();
    chartView->setVisible(1);

    layout->addLayout(buttons);
    layout->addWidget(chartView);
    setLayout(layout);

    connect(exclusiveCheck, &QButtonGroup::idClicked, chartView, &customChartView::setMode);
}

chartWindow::~chartWindow(){
    delete layout;
    delete chartView;
}

void chartWindow::changeChart(QtCharts::QChart *chart){
    chartView->setChart(chart);
}
