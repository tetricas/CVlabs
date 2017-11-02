#include "Segments/SegmentsFieldWidget.h"

#include <QPainter>

CSegmentsFieldWidget::CSegmentsFieldWidget( QWidget* parent ) :
    QWidget( parent )
{}

void CSegmentsFieldWidget::paintEvent( QPaintEvent* event )
{
    QPainter painter(this);
}
