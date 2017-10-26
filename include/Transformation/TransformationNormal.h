#ifndef TRANSFORMATIONNORMAL_H
#define TRANSFORMATIONNORMAL_H

#include "TransformationBase.h"
#include <QGenericMatrix>

class CTransformationNormal: public CTransformationBase
{

public:
    explicit CTransformationNormal( Ui::TransformationWidget* ui );

    virtual void getCoords() override;

    virtual void scaleProcess() override;
    virtual void rotateProcess() override;
    virtual void moveProcess() override;

    virtual void outputResults() override;

protected:
    QGenericMatrix<1, 2, qreal> m_inputVector;
    QGenericMatrix<1, 2, qreal> m_coordsVector;
    QGenericMatrix<2, 2, qreal> m_transformationMatrix;
};

#endif // TRANSFORMATIONNORMAL_H
