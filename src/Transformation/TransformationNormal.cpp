#include "Transformation/TransformationNormal.h"
#include "ui_transformationwidget.h"

#include <QRegExp>
#include <QtMath>

CTransformationNormal::CTransformationNormal( Ui::TransformationWidget *ui ) :
    CTransformationBase( ui )
{
    m_inputVector.fill( 0 );
    m_coordsVector.fill( 0 );
    m_transformationMatrix.fill( 0 );
}

void CTransformationNormal::getCoords()
{
    if( !m_itHasLiterals )
    {
        m_coordsVector( 0, 0 ) = m_ui->xCoordEdit->toPlainText().toInt();
        m_coordsVector( 1, 0 ) = m_ui->yCoordEdit->toPlainText().toInt();
    }
    else
    {
        QRegExp digitReg("(\\d+|-\\d+)");

        digitReg.indexIn( m_ui->xCoordEdit->toPlainText() );
        m_coordsVector( 0, 0 ) = digitReg.cap(1).toInt();

        digitReg.indexIn( m_ui->yCoordEdit->toPlainText() );
        m_coordsVector( 1, 0 ) = digitReg.cap(1).toInt();
    }
    m_inputVector( 0, 0 ) = m_coordsVector( 0, 0 );
    m_inputVector( 1, 0 ) = m_coordsVector( 1, 0 );
}

void CTransformationNormal::scaleProcess()
{
    m_transformationMatrix.fill( 0 );
    m_transformationMatrix( 0, 0 ) = m_params.first;
    m_transformationMatrix( 1, 1 ) = m_params.second;

    m_coordsVector = m_transformationMatrix * m_coordsVector;
}

void CTransformationNormal::rotateProcess()
{
    m_transformationMatrix( 0, 0 ) = m_transformationMatrix( 1, 1 ) = qCos( m_params.first );
    m_transformationMatrix( 0, 1 ) = m_transformationMatrix( 1, 0 ) = qSin( m_params.first );

    if( m_params.first < 0 )
        m_transformationMatrix( m_leftBottom.first, m_leftBottom.second ) *= -1;
    else
        m_transformationMatrix( m_topRight.first, m_topRight.second ) *= -1;

    m_coordsVector = m_transformationMatrix * m_coordsVector;
}

void CTransformationNormal::moveProcess()
{
    m_coordsVector( 0, 0 ) += m_params.first;
    m_coordsVector( 1, 0 ) += m_params.second;
    m_transformationMatrix.fill( 0 );
}

void CTransformationNormal::outputResults()
{
    QString input, transformation, output;
    QTextStream streamIn(&input), streamTrans(&transformation), streamOut(&output);

    streamIn << "Input vector: \n"
             << "|\t "<< m_inputVector( 0, 0 ) << (m_itHasLiterals? "x": " ")<< "\t|\n"
             << "|\t "<< m_inputVector( 1, 0 ) << (m_itHasLiterals? "y": " ")<< "\t|";

    streamTrans << "Transformation matrix: \n"
                << "|\t"<< m_transformationMatrix( 0, 0 )<< ",\t"<< m_transformationMatrix( 0, 1 ) << "\t|\n"
                << "|\t"<< m_transformationMatrix( 1, 0 )<< ",\t"<< m_transformationMatrix( 1, 1 ) << "\t|";

    streamOut << "Resul vector: \n"
              << "|\t "<< m_coordsVector( 0, 0 ) << (m_itHasLiterals? "x": " ")<< "\t|\n"
              << "|\t "<< m_coordsVector( 1, 0 ) << (m_itHasLiterals? "y": " ")<< "\t|";

    m_ui->inputLabel->setText( input );
    m_ui->transformLabel->setText( transformation );
    m_ui->outputLabel->setText( output );
}
