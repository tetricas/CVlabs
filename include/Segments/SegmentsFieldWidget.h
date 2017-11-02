#ifndef SEGMENTSFIELDWIDGET_H
#define SEGMENTSFIELDWIDGET_H

#include <QWidget>

class CSegmentsFieldWidget: public QWidget
{
    Q_OBJECT

public:
    explicit CSegmentsFieldWidget( QWidget* parent = 0 );

protected:
    void paintEvent( QPaintEvent* event );
};

#endif // SEGMENTSFIELDWIDGET_H
