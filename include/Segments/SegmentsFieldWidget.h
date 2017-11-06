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
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent* event);

    void mousePressEvent( QMouseEvent* event );
    void mouseReleaseEvent( QMouseEvent* event );
    void mouseMoveEvent( QMouseEvent* event );

private slots:
    void bresenhamTimerSlot();

private:
    void resetPoints();

    QPoint m_startPoint;
    QPoint m_endPoint;
    bool m_isProcessing;

    QVector<QPoint> m_bresenhamPoints;
    QPoint m_diffPoint;
    QPoint m_lengthPoint;
    QPoint m_currentPoint;
    int m_diff;
    int m_length;
    bool m_isXGreater;

    QTimer m_bresenhamTimer;
};

#endif // SEGMENTSFIELDWIDGET_H
