#ifndef SEGMENTSFIELDWIDGET_H
#define SEGMENTSFIELDWIDGET_H

#include <QWidget>
#include <QTimer>

class CSegmentsFieldWidget: public QWidget
{
    Q_OBJECT

public:
    explicit CSegmentsFieldWidget( QWidget* parent = 0 );

public slots:
    void startProcess();
    void clearField();

protected:
    void paintEvent( QPaintEvent* event );
    void resizeEvent( QResizeEvent* event );

    void mousePressEvent( QMouseEvent* event );
    void mouseReleaseEvent( QMouseEvent* event );
    void mouseMoveEvent( QMouseEvent* event );

private slots:
    void gridTimerSlot();

private:
    QPoint m_startPoint;
    QPoint m_endPoint;

    bool m_isHaveGrid;
    bool m_isGridPainting;
    size_t maxGridStepCount;
    size_t m_gridStepCount;
    size_t m_gridStep;

    QTimer m_gridTimer;
};

#endif // SEGMENTSFIELDWIDGET_H
