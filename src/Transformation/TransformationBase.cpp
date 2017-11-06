#include "Transformation/TransformationBase.h"
#include "ui_transformationwidget.h"

#include <QRegExp>

CTransformationBase::CTransformationBase(Ui::TransformationWidget* ui , QTransform &transformation) :
    m_ui(ui),
    m_transformation( transformation )
{
    m_leftBottom.first = m_topRight.second = 1;     //{{ 0, R }     first - row
    m_leftBottom.second = m_topRight.first = 0;     // { L, 0 }}    second - column
    m_itHasLiterals = false;
}

bool CTransformationBase::checkInput(bool isInput)
{
    QRegExp xCoorgReg("(\\d+|-\\d+)(x)"),
            yCoorgReg("(\\d+|-\\d+)(y)"),
            digitReg("(\\d+|-\\d+)");

    // at the following comments "*" - any digit
    if( ( xCoorgReg.exactMatch( m_ui->xCoordEdit->toPlainText() ) &&
          !yCoorgReg.exactMatch( m_ui->yCoordEdit->toPlainText() ) ) ||  // *x and !*y
            ( digitReg.exactMatch( m_ui->xCoordEdit->toPlainText() ) &&
              !digitReg.exactMatch( m_ui->yCoordEdit->toPlainText() ) ) ||  // * and !*
            ( !xCoorgReg.exactMatch( m_ui->xCoordEdit->toPlainText() ) &&
              yCoorgReg.exactMatch( m_ui->yCoordEdit->toPlainText() ) ) ||  // *!x and *y
            ( !digitReg.exactMatch( m_ui->xCoordEdit->toPlainText() ) &&
              digitReg.exactMatch( m_ui->yCoordEdit->toPlainText() ) ) )  // !* and *
        return false;

    if( xCoorgReg.exactMatch( m_ui->xCoordEdit->toPlainText() ) &&
            yCoorgReg.exactMatch( m_ui->yCoordEdit->toPlainText() ) )  // *x and *y
        m_itHasLiterals = true;
    else                                        // * and *
        m_itHasLiterals = false;

    if( !digitReg.exactMatch( m_ui->zCoordEdit->toPlainText() ) ||
            !digitReg.exactMatch( m_ui->firstParameter->toPlainText() ) ||
            ( isInput && !digitReg.exactMatch( m_ui->secondParameter->toPlainText() ) ) )
        return false;

    return true;
}

void CTransformationBase::getParams()
{
    m_params = QPair<qreal, qreal>( m_ui->firstParameter->toPlainText().toInt(),
                                    m_ui->secondParameter->toPlainText().toInt() );
}
