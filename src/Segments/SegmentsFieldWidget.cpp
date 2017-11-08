#include "Segments/SegmentsFieldWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>

CSegmentsFieldWidget::CSegmentsFieldWidget( QWidget* parent ) :
    QWidget( parent ),
    m_isProcessing( false )
{
    resetPoints();

    m_bresenhamTimer.setInterval( 10 );
    connect( &m_bresenhamTimer, &QTimer::timeout, this, &CSegmentsFieldWidget::bresenhamTimerSlot );
}

void CSegmentsFieldWidget::startProcess()
{
    m_bresenhamPoints.clear();
    QPoint diff( m_endPoint.x() - m_startPoint.x(), m_endPoint.y() - m_startPoint.y() );
    m_diffPoint = QPoint( ( diff.x() >= 0 ? 1 : -1), ( diff.y() >= 0 ? 1 : -1) );

    m_lengthPoint = QPoint( qAbs( diff.x() ), qAbs( diff.y() ) );

    m_length = qMax( m_lengthPoint.x(), m_lengthPoint.y() );

    if( m_length == 0 )
    {
          m_bresenhamPoints.push_back( { m_startPoint.x(), m_startPoint.y() } );
          update();
    }

    m_currentPoint = m_startPoint;
    ++m_length;

    if( m_lengthPoint.y() <= m_lengthPoint.x() )
    {
        m_isXGreater = true;
        m_diff = -m_lengthPoint.x();
    }
    else
    {
        m_isXGreater = false;
        m_diff = -m_lengthPoint.y();
    }

    m_isProcessing = true;
    resetPoints();
    m_bresenhamTimer.start();
}

void CSegmentsFieldWidget::clearField()
{
    resetPoints();

    m_isProcessing = false;
    m_bresenhamTimer.stop();
    m_bresenhamPoints.clear();
    update();
}

void CSegmentsFieldWidget::paintEvent( QPaintEvent* /*event*/ )
{
    QPainter painter(this);
    painter.setPen( Qt::black );

    foreach (auto point, m_bresenhamPoints)
        painter.drawPoint( point );

    if( !m_isProcessing )
        painter.drawLine(m_startPoint, m_endPoint);
}

void CSegmentsFieldWidget::resizeEvent( QResizeEvent* event )
{
    if( width() < height() )
        resize( width(), width() );
    else
        resize( height(), height() );

    if( m_isProcessing )
        event->ignore();
}

void CSegmentsFieldWidget::mousePressEvent( QMouseEvent* event )
{
    if( !m_isProcessing )
        m_startPoint = event->pos();
}

void CSegmentsFieldWidget::mouseReleaseEvent( QMouseEvent* event )
{
    if( !m_isProcessing )
        m_endPoint = event->pos();
}

void CSegmentsFieldWidget::mouseMoveEvent(QMouseEvent* event)
{
    if( !m_isProcessing )
    {
        m_endPoint = event->pos();
        update();
    }
}

void CSegmentsFieldWidget::bresenhamTimerSlot()
{
    if( m_length-- )
    {
        m_bresenhamPoints.push_back( { m_currentPoint.x(), m_currentPoint.y() } );
        update();
        if( m_isXGreater )
        {
            m_currentPoint.setX( m_currentPoint.x() + m_diffPoint.x() );
            m_diff += 2 * m_lengthPoint.y();
            if (m_diff > 0)
            {
                m_diff -= 2 * m_lengthPoint.x();
                m_currentPoint.setY( m_currentPoint.y() + m_diffPoint.y() );
            }
        }
        else
        {
            m_currentPoint.setY( m_currentPoint.y() + m_diffPoint.y() );
            m_diff += 2 * m_lengthPoint.x();
            if (m_diff > 0)
            {
                m_diff -= 2 * m_lengthPoint.y();
                m_currentPoint.setX( m_currentPoint.x() + m_diffPoint.x() );
            }
        }
    }
    else
    {
        m_bresenhamTimer.stop();
    }
}

void CSegmentsFieldWidget::resetPoints()
{
    m_startPoint = QPoint( -1000, -1000);
    m_endPoint = QPoint( -1000, -1000 );
}
