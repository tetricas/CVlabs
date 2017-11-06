#ifndef TRANSFORMATIONBASE_H
#define TRANSFORMATIONBASE_H

#include <QSharedPointer>
#include <QPair>

namespace Ui {
class TransformationWidget;
}

class CTransformationBase
{
public:
    explicit CTransformationBase( Ui::TransformationWidget* ui, QTransform& transformation );

    bool checkInput( bool isInput );
    void getParams();
    virtual void getCoords() = 0;

    virtual void scaleProcess() = 0;
    virtual void rotateProcess() = 0;
    virtual void moveProcess() = 0;

    virtual void outputResults() = 0;
    virtual void setTransformation() = 0;

protected:
    Ui::TransformationWidget* m_ui;
    bool m_itHasLiterals;

    QTransform& m_transformation;

    QPair<qreal, qreal> m_params;
    QPair<qreal, qreal> m_leftBottom;
    QPair<qreal, qreal> m_topRight;
};

#endif // TRANSFORMATIONBASE_H
