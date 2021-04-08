#include <QPoint>
#include "customChartView.h"


customChartView::customChartView(){
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

        r.moveCenter((ogP + p) / 2);

    }

    else if(event->angleDelta().y() < 0){
        printf("WOOOOOO\n");
        r = chart()->plotArea();

        QPointF ogP = r.center();
        QPointF p = event->position();

        r.setWidth(r.width() * 2);
        r.setHeight(r.height() * 2);

        r.moveCenter(2*ogP - p);
    }

    chart()->zoomIn(r);
}
