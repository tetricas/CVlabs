#ifndef TRANSFORMATIONWIDGET_H
#define TRANSFORMATIONWIDGET_H

#include <QWidget>
#include <QGenericMatrix>

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
    void getParams();

    void scaleProcess();
    void rotateProcess();
    void moveProcess();

    Ui::TransformationWidget *m_ui;

    ETransformaions m_currentTransformation;
    bool m_itHasLiterals;
    QGenericMatrix<1, 2, qreal> m_coordsVector;
    QPair<int, int> m_params;
};

#endif // TRANSFORMATIONWIDGET_H
