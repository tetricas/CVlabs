#include "Segments/SegmentsFieldWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>

CSegmentsFieldWidget::CSegmentsFieldWidget( QWidget* parent ) :
    QWidget( parent ),
    m_isHaveGrid( false ),
    m_isGridPainting( false )
{
    m_gridTimer.setInterval( 100 );
    connect( &m_gridTimer, &QTimer::timeout, this, &CSegmentsFieldWidget::gridTimerSlot );
}

void CSegmentsFieldWidget::startProcess()
{
    m_gridStepCount = 0;
    m_isHaveGrid = true;
    m_isGridPainting = true;
    m_gridTimer.start();
}

void CSegmentsFieldWidget::clearField()
{
    m_startPoint = QPoint( -1, -1 );
    m_endPoint = QPoint( -1, -1 );

    m_isHaveGrid = false;
    m_isGridPainting = false;
    m_gridTimer.stop();
    update();
}

void CSegmentsFieldWidget::paintEvent( QPaintEvent* event )
{
    QPainter painter(this);

    if( m_isHaveGrid )
    {
        painter.setPen( Qt::lightGray );
        for( int i = 0; i < m_gridStepCount; ++i )
        {
            painter.drawLine( 0, i * m_gridStep, width(), i * m_gridStep );
            painter.drawLine( i * m_gridStep, 0, i * m_gridStep, height() );
        }
    }

    painter.setPen( Qt::black );
    painter.drawLine(m_startPoint, m_endPoint);
}

void CSegmentsFieldWidget::resizeEvent( QResizeEvent* event )
{
    size_t maxSide = width() > height() ? width() : height();
    m_gridStep = 5;
    maxGridStepCount = maxSide / m_gridStep;
}

void CSegmentsFieldWidget::mousePressEvent( QMouseEvent* event )
{
    m_startPoint = event->pos();
}

void CSegmentsFieldWidget::mouseReleaseEvent( QMouseEvent* event )
{
    m_endPoint = event->pos();
}

void CSegmentsFieldWidget::mouseMoveEvent(QMouseEvent* event)
{
    m_endPoint = event->pos();
    update();
}

void CSegmentsFieldWidget::gridTimerSlot()
{
    if( m_isGridPainting )
    {
        if( m_gridStepCount < maxGridStepCount)
            ++m_gridStepCount;
        else
            m_isGridPainting = false;
        update();
    }
    else
    {
        m_gridTimer.stop();
        //TODO: next steps
    }
}
