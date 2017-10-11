#ifndef TRANSFORMATIONWIDGET_H
#define TRANSFORMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class TransformationWidget;
}

class CTransformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTransformationWidget( QWidget *parent = 0 );
    ~CTransformationWidget();

private slots:
    void updateSettings( const QString& name );

private:
    void setupUi();

    Ui::TransformationWidget *m_ui;
};

#endif // TRANSFORMATIONWIDGET_H
