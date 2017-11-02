#include "Segments/SegmentsWidget.h"
#include "ui_segmentswidget.h"

#include <QPainter>

#include "Segments/SegmentsFieldWidget.h"

CSegmentsWidget::CSegmentsWidget( QWidget* parent ) :
    QWidget( parent ),
    m_ui( new Ui::SegmentsWidget )
{
    m_ui->setupUi(this);
    setupCommunication();
}

void CSegmentsWidget::setupCommunication()
{
    connect( m_ui->startButton, &QPushButton::clicked, m_ui->field, &CSegmentsFieldWidget::startProcess );
    connect( m_ui->clearButton, &QPushButton::clicked, m_ui->field, &CSegmentsFieldWidget::clearField );
}
