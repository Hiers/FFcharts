#pragma once
#include <QtCharts/QChartView>
#include <QValueAxis>

class customChartView:public QtCharts::QChartView{
    public:
        customChartView();
        ~customChartView();
        //void setChart(QtCharts::QChart *chart);

    private:
        int mode;
        int t_zoomed;
        QRectF ogzoom;
        QPoint previous_pos;
        /*QtCharts::QValueAxis *xaxis;
        QtCharts::QValueAxis *yaxis;*/

    protected:
        void wheelEvent(QWheelEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;

    public slots:
        void setMode(int id);
};
