#ifndef TRANSFORMATIONHOMOGENEOUS_H
#define TRANSFORMATIONWIDGET_H

#include "TransformationBase.h"
#include <QGenericMatrix>

class CTransformationHomogeneous: public CTransformationBase
{

public:
    explicit CTransformationHomogeneous( Ui::TransformationWidget *ui, QTransform& transformation, int coefficient );

    virtual void getCoords() override;

    virtual void scaleProcess() override;
    virtual void rotateProcess() override;
    virtual void moveProcess() override;

    virtual void outputResults() override;
    virtual void setTransformation() override;

protected:
    QGenericMatrix<1, 3, qreal> m_inputVector;
    QGenericMatrix<1, 3, qreal> m_coordsVector;
    QGenericMatrix<3, 3, qreal> m_transformationMatrix;

private:
    int m_coefficient;
};

#endif // TRANSFORMATIONWIDGET_H
