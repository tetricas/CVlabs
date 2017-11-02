#include "Segments/SegmentsWidget.h"
#include "ui_segmentswidget.h"

#include <QPainter>

CSegmentsWidget::CSegmentsWidget( QWidget* parent ) :
    QWidget( parent ),
    m_ui( new Ui::SegmentsWidget )
{
    m_ui->setupUi(this);
}
