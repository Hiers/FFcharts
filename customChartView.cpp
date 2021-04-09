#include <QPoint>
#include "customChartView.h"


customChartView::customChartView(){
    //setRenderHint(QPainter::Antialiasing);
}

customChartView::~customChartView(){
}

void customChartView::wheelEvent(QWheelEvent *event){
    QRectF r;

    if(event->angleDelta().y() > 0){
        r = chart()->plotArea();

        QPointF ogP = r.center();
        QPointF p = event->position();

        r.setWidth(r.width() / 2);
        r.setHeight(r.height() / 2);

        r.moveCenter((ogP + p) / 2);//best approximations I could get

    }

    else if(event->angleDelta().y() < 0){
        r = chart()->plotArea();

        QPointF ogP = r.center();
        QPointF p = event->position();

        r.setWidth(r.width() * 2);
        r.setHeight(r.height() * 2);

        r.moveCenter(2*ogP - p);//best approximations I could get
    }

    chart()->zoomIn(r);
}

void customChartView::setMode(int id){
    if(id == 0)
        mode = 0;
    else
        mode = 1;
}
        

void customChartView::mousePressEvent(QMouseEvent *event){
    if(mode == 0)
        previous_pos = event->globalPos();
    else
        QtCharts::QChartView::mousePressEvent(event);
}

void customChartView::mouseMoveEvent(QMouseEvent *event){
    if(mode == 0){
        QPoint current_pos;
        if(event->buttons() & Qt::LeftButton){
            current_pos = event->globalPos();
    
            
            int dx = current_pos.x() - previous_pos.x();
            int dy = current_pos.y() - previous_pos.y();
    
            chart()->scroll(-dx, dy);
        }

        previous_pos = current_pos;
    }
    else
        QtCharts::QChartView::mouseMoveEvent(event);
}




