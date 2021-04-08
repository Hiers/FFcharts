#pragma once
#include <QtCharts/QChartView>

class customChartView:public QtCharts::QChartView{
    public:
        customChartView();
        ~customChartView();

    protected:
        void wheelEvent(QWheelEvent *event) override;
        /*void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;*/

};
