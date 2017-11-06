#ifndef TRANSFORMATIONNORMAL_H
#define TRANSFORMATIONNORMAL_H

#include "TransformationBase.h"
#include <QGenericMatrix>

class CTransformationNormal: public CTransformationBase
{

public:
    explicit CTransformationNormal(Ui::TransformationWidget* ui , QTransform &transformation);

    virtual void getCoords() override;

    virtual void scaleProcess() override;
    virtual void rotateProcess() override;
    virtual void moveProcess() override;

    virtual void outputResults() override;
    virtual void setTransformation() override;

protected:
    QGenericMatrix<1, 2, qreal> m_inputVector;
    QGenericMatrix<1, 2, qreal> m_coordsVector;
    QGenericMatrix<2, 2, qreal> m_transformationMatrix;

    bool m_isTranslation;
    int m_dx;
    int m_dy;
};

#endif // TRANSFORMATIONNORMAL_H
