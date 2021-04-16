#include <QFileDialog>
#include "mainWindow.h"
#include <stdio.h>

mainWindow::mainWindow(){
    relativePath = "";
    data = NULL;
    grid = new QGridLayout();

    openBtn = new QPushButton("Open File");
    addBtn = new QPushButton("Add Series");
    addBtn->setEnabled(0);
    chartBtn = new QPushButton("Show chart");
    chartBtn->setEnabled(0);

    grid->addWidget(openBtn, 0, 0);
    grid->addWidget(addBtn, 0, 2);
    grid->addWidget(chartBtn, 0, 3);

    
    tabs = new QTabWidget();
    infoTab = new QWidget();
    optionsTab = new QWidget();


    /*
     * SERIES TAB
     */
    listSeries = new QListWidget();
    gridInfo = new QGridLayout();

    name = new QLabel("Name:");
    nframes = new QLabel("N. of frames:");
    vmaf = new QLabel("VMAF:");
    typelabel = new QLabel("Type:");
    seriesCount = 1;

    gridInfo->addWidget(name, 1, 1);
    gridInfo->addWidget(nframes, 1, 2);
    gridInfo->addWidget(vmaf, 2, 1);
    gridInfo->addWidget(typelabel, 2, 2);
    gridInfo->setColumnMinimumWidth(0, 10);
    gridInfo->setColumnMinimumWidth(3, 10);
    gridInfo->setRowMinimumHeight(0, 5);
    gridInfo->setRowMinimumHeight(3, 10);

    gridInfo->addWidget(listSeries, 4, 0, 1, 4);
    
    removeBtn = new QPushButton("Remove");
    gridInfo->addWidget(removeBtn, 5, 0, 1, 4);

    infoTab->setLayout(gridInfo);
    /*
     * SERIES TAB
     */


    /*
     * OPTIONS TAB
     */
    gridOptions = new QGridLayout();

    subsampleSet = new QSpinBox();
    subsampleSet->setRange(1, 100);
    sampleLabel = new QLabel("Subsampling ");
    sampleLayout = new QHBoxLayout();
    sampleLayout->addWidget(sampleLabel);
    sampleLayout->addWidget(subsampleSet);

    vmafFrame = new QCheckBox("Vmaf(frames)");
    vmafFrame->setChecked(1);
    vmafCrf = new QCheckBox("Vmaf(crf)");
    vmafCrf->setEnabled(0);
    bitrateFrame = new QCheckBox("Bitrate(frames)");
    bitrateFrame->setEnabled(0);

    //Logical button group. Needed for exclusive checks.
    chartType = new QButtonGroup();
    chartType->addButton(vmafFrame);
    chartType->addButton(vmafCrf);
    chartType->addButton(bitrateFrame);
    chartType->setExclusive(1);

    groupBox = new QGroupBox();
    boxLayout = new QVBoxLayout();
    boxLayout->addStretch(1);
    boxLayout->addWidget(vmafFrame);
    boxLayout->addWidget(vmafCrf);
    boxLayout->addWidget(bitrateFrame);
    boxLayout->addStretch(1);
    groupBox->setLayout(boxLayout);

    gridOptions->addLayout(sampleLayout, 0, 0);
    gridOptions->setColumnStretch(1, 1);
    gridOptions->addWidget(groupBox, 2, 0);
    gridOptions->setRowStretch(3, 1);

    optionsTab->setLayout(gridOptions);
    /*
     * OPTIONS TAB
     */


    tabs->addTab(infoTab, "Series");
    tabs->addTab(optionsTab, "Options");

    grid->addWidget(tabs, 2, 0, 1, 4);
    
    centralWidget = new QWidget();
    centralWidget->setLayout(grid);
    setCentralWidget(centralWidget);


    worker = new Worker();
    worker->moveToThread(&thread);
    charts = new Charts();
    chart = NULL;

    connect(openBtn, &QPushButton::clicked, this, &mainWindow::chooseFile);
    connect(addBtn, &QPushButton::clicked, this, &mainWindow::requestParse);
    connect(chartBtn, &QPushButton::clicked, this, &mainWindow::requestChart);

    connect(removeBtn, &QPushButton::clicked, this, &mainWindow::requestRemove);

    connect(this, &mainWindow::parseSignal, worker, &Worker::parseFile);
    connect(worker, &Worker::placeholder, this, &mainWindow::setInfo);
    

    thread.start();
    window = NULL;
}

mainWindow::~mainWindow(){
    delete centralWidget;
    delete window;

    delete worker;
    thread.quit();
    thread.wait();
}

//if the close event isn't reimplemented, secondary window will not close if it is open
void mainWindow::closeEvent(QCloseEvent *event){
    if(window)
        window->close();
    QMainWindow::closeEvent(event);
}



void mainWindow::chooseFile(){
    if(!filePath.isEmpty())
        filePath.clear();
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("JSON(*.json);;XML (*.xml)"));
    if(!filePath.isEmpty()){
        relativePath = QDir::toNativeSeparators(QDir("./").relativeFilePath(filePath));
        QString label = "Name: ";
        label.append(relativePath);
        name->setText(label);
        
        emit parseSignal(relativePath);
        
    }
}

void mainWindow::setInfo(point *dataSet){
    data = dataSet;
    QString label = "N. of frames: ";
    label.append(QString::number(data[0].y));
    nframes->setText(label);
    label.clear();

    if(data[0].x < 0){
        label.append("Bitrate: ");
        label.append(QString::number(data[0].x * (-1)));
        vmaf->setText(label);   
        
        label.clear();
        label.append("Type: ");
        label.append("Bitrate/frame");
        typelabel->setText(label);
    }
    else{
        label.append("VMAF: ");
        label.append(QString::number(data[0].x));
        vmaf->setText(label);   

        label.clear();
        label.append("Type: ");
        label.append("Vmaf/frame");
        typelabel->setText(label);
    }
    addBtn->setEnabled(1);
}

void mainWindow::requestParse(){
    
    QString listItem;
    listItem.append(relativePath);

    listSeries->addItem(listItem);
    type = 0;
    chart = charts->createChart(data, type, subsampleSet->value());
    if(chart)
        chartBtn->setEnabled(1);
}

void mainWindow::requestChart(){

    if(!window){
        window = new chartWindow();
        window->changeChart(chart);
        installEventFilter(window);
    }
    
    
    if(!window->isVisible()){
        window->resize(450, 350);
        window->setWindowTitle("Chart View");
        window->show();
    }
}

void mainWindow::requestRemove(){
    QListWidgetItem *item = listSeries->currentItem();
    int row = item->listWidget()->row(item);
    listSeries->takeItem(row);
    delete item;

    chart = charts->removeSeries(row);
}
