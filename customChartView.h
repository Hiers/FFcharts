#pragma once
#include <QtCharts/QChartView>

class customChartView:public QtCharts::QChartView{
    public:
        customChartView();
        ~customChartView();

    private:
        int mode;
        QPoint previous_pos;

    protected:
        void wheelEvent(QWheelEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        /*void mouseReleaseEvent(QMouseEvent *event) override;*/
        void mouseMoveEvent(QMouseEvent *event) override;

    public slots:
        void setMode(int id);
};
