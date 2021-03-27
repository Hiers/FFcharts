#pragma once
#include <forward_list>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QString>
#include <QThread>

#include <QTabWidget>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>

#include "worker.h"
#include "charts.h"
#include "chartWindow.h"

class mainWindow:public QMainWindow{

    Q_OBJECT

    public:
        mainWindow();
        ~mainWindow();

        Worker *worker;
        
        QString relativePath;

    protected:
        void closeEvent(QCloseEvent *event) override;

    private:
    
        point *data;
        int type;
        int n_subsample;

        QtCharts::QChart *chart;
    
        QGridLayout *grid;
        QWidget *centralWidget;
        QLabel *chosenFile;
        QPushButton *openBtn;
        QPushButton *addBtn;
        QPushButton *chartBtn;
        QString filePath;

        QWidget *infoTab;
        QWidget *optionsTab;
        QTabWidget *tabs;

        QListWidget *listSeries;
        QGridLayout *gridInfo;
        QLabel *name;
        QLabel *nframes;
        QLabel *typelabel;
        QLabel *vmaf;
        int seriesCount;
        QPushButton *removeBtn;

        QGridLayout *gridOptions;
        QSpinBox *subsampleSet;
        QLabel *sampleLabel;
        QHBoxLayout *sampleLayout;
        QCheckBox *vmafFrame;
        QCheckBox *vmafCrf;
        QCheckBox *bitrateFrame;
        QButtonGroup *chartType;
        QGroupBox *groupBox;
        QVBoxLayout *boxLayout;


        QThread thread;

        chartWindow *window;

        Charts *charts;


    public slots:
        void chooseFile();
        void setInfo(point *dataSet);

    private slots:
        void requestParse();
        void requestChart();
        void requestRemove();

    signals:
        void parseSignal(QString fileName);
};
