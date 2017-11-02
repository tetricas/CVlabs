#ifndef SEGMENTSWIDGET_H
#define SEGMENTSWIDGET_H

#include <QWidget>

namespace Ui {
class SegmentsWidget;
}

class CSegmentsWidget: public QWidget
{
    Q_OBJECT

public:
    explicit CSegmentsWidget( QWidget *parent = 0 );

private:
    Ui::SegmentsWidget* m_ui;
};

#endif // SEGMENTSWIDGET_H
