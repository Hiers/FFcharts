#include <QPoint>
#include "customChartView.h"


customChartView::customChartView(){
    //setRenderHint(QPainter::Antialiasing);
    setRubberBand(QChartView::RectangleRubberBand);
    t_zoomed = 0;
    mode = 0;
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
        t_zoomed++;
    }

    else if(event->angleDelta().y() < 0){
        if(t_zoomed > 0){
            r = chart()->plotArea();
    
            QPointF ogP = r.center();
            QPointF p = event->position();
    
            r.setWidth(r.width() * 2);
            r.setHeight(r.height() * 2);
    
            r.moveCenter(2*ogP - p);//best approximations I could get
            t_zoomed--;
        }
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
        QChartView::mousePressEvent(event);
}

void customChartView::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() & Qt::RightButton){
        if(chart()->isZoomed()){
            chart()->zoomReset();
        }
    }
    else
        QChartView::mouseReleaseEvent(event);
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
        QChartView::mouseMoveEvent(event);
}


/*void customChartView::setChart(QtCharts::QChart *chart){
    QChartView::setChart(chart);
    xaxis = qobject_cast<QtCharts::QValueAxis*>(this->chart()->axes().at(0));
    yaxis = qobject_cast<QtCharts::QValueAxis*>(this->chart()->axes().at(1));
}*/


