#ifndef TRANSFORMATIONWIDGET_H
#define TRANSFORMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class TransformationWidget;
}

class CTransformationWidget: public QWidget
{
    Q_OBJECT

    enum class ETransformaions
    {
        Scale,
        Rotate,
        Move
    };

public:
    explicit CTransformationWidget( QWidget *parent = 0 );
    ~CTransformationWidget();

private slots:
    void updateSettings( const QString& name );
    void startProcessing();

private:
    void setupUi();
    bool checkInput();
    void getCoords();

    void scaleProcess();
    void rotateProcess();
    void moveProcess();

    Ui::TransformationWidget *m_ui;

    ETransformaions m_currentTransformation;
    bool m_itHasLiterals;
    QPoint m_coords;
};

#endif // TRANSFORMATIONWIDGET_H
