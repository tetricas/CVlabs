#ifndef TRANSFORMATIONWIDGET_H
#define TRANSFORMATIONWIDGET_H

#include <QWidget>
#include <QGenericMatrix>
#include <QGraphicsView>

#include "TransformationNormal.h"
#include "TransformationHomogeneous.h"

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
    explicit CTransformationWidget( QWidget *parent = nullptr );
    ~CTransformationWidget();

private slots:
    void updateSettings( const QString& name );
    void startProcessing();
    void visualize();

private:
    void setupUi();
    bool checkHomogeneous();

    Ui::TransformationWidget *m_ui;

    QSharedPointer<QGraphicsPixmapItem> item;
    QTransform m_transform;
    bool m_hasResults;
    ETransformaions m_currentTransformation;
    QSharedPointer<CTransformationBase> m_transformation;
};

#endif // TRANSFORMATIONWIDGET_H
