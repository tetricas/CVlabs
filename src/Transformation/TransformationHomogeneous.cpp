#include "Transformation/TransformationHomogeneous.h"
#include "ui_transformationwidget.h"

#include <QRegExp>
#include <QtMath>

CTransformationHomogeneous::CTransformationHomogeneous(Ui::TransformationWidget *ui , QTransform &transformation, int coefficient) :
    CTransformationBase( ui, transformation ),
    m_coefficient( coefficient )
{
    m_inputVector.fill( 0 );
    m_coordsVector.fill( 0 );
    m_transformationMatrix.fill( 0 );
}

void CTransformationHomogeneous::getCoords()
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
    m_inputVector( 2, 0 ) = m_coefficient;

    m_coordsVector( 0, 0 ) /= m_coefficient;
    m_coordsVector( 1, 0 ) /= m_coefficient;
    m_coordsVector( 2, 0 ) = 1;
}

void CTransformationHomogeneous::scaleProcess()
{
    m_transformationMatrix.fill( 0 );
    m_transformationMatrix( 0, 0 ) = m_params.first;
    m_transformationMatrix( 1, 1 ) = m_params.second;
    m_transformationMatrix( 2, 2 ) = 1;

    m_coordsVector = m_transformationMatrix * m_coordsVector;
}

void CTransformationHomogeneous::rotateProcess()
{
    m_transformationMatrix.fill( 0 );
    m_transformationMatrix( 0, 0 ) = m_transformationMatrix( 1, 1 ) = qCos( qDegreesToRadians( m_params.first ) );
    m_transformationMatrix( 1, 0 ) = m_transformationMatrix( 0, 1 ) = qSin( qDegreesToRadians( m_params.first ) );
    m_transformationMatrix( 2, 2 ) = 1;

    m_coordsVector = m_transformationMatrix * m_coordsVector;
}

void CTransformationHomogeneous::moveProcess()
{
    m_transformationMatrix.fill( 0 );
    m_transformationMatrix( 0, 0 ) = 1;
    m_transformationMatrix( 1, 1 ) = 1;
    m_transformationMatrix( 2, 2 ) = 1;
    m_transformationMatrix( 0, 2 ) = m_params.first;
    m_transformationMatrix( 1, 2 ) = m_params.second;

    m_coordsVector = m_transformationMatrix * m_coordsVector;
}

void CTransformationHomogeneous::outputResults()
{
    QString input, transformation, output;
    QTextStream streamIn(&input), streamTrans(&transformation), streamOut(&output);

    m_coordsVector( 0, 0 ) *= m_coefficient;
    m_coordsVector( 1, 0 ) *= m_coefficient;
    m_coordsVector( 2, 0 ) = m_coefficient;

    streamIn << "Input vector: \n"
             << "|\t "<< m_inputVector( 0, 0 ) << (m_itHasLiterals? "x": " ")<< "\t|\n"
             << "|\t "<< m_inputVector( 1, 0 ) << (m_itHasLiterals? "y": " ")<< "\t|\n"
             << "|\t "<< m_inputVector( 2, 0 ) << (m_itHasLiterals? "y": " ")<< "\t|";

    streamTrans << "Transformation matrix: \n"
                << "|\t"<< m_transformationMatrix( 0, 0 )<< ",\t"<< m_transformationMatrix( 0, 1 ) << ",\t"
                << m_transformationMatrix( 0, 2 ) << "\t|\n"
                << "|\t"<< m_transformationMatrix( 1, 0 )<< ",\t"<< m_transformationMatrix( 1, 1 ) << ",\t"
                << m_transformationMatrix( 1, 2 ) << "\t|\n"
                << "|\t"<< m_transformationMatrix( 2, 0 )<< ",\t"<< m_transformationMatrix( 2, 1 ) << ",\t"
                << m_transformationMatrix( 2, 2 ) << "\t|";

    streamOut << "Resul vector: \n"
              << "|\t "<< m_coordsVector( 0, 0 ) << (m_itHasLiterals? "x": " ")<< "\t|\n"
              << "|\t "<< m_coordsVector( 1, 0 ) << (m_itHasLiterals? "y": " ")<< "\t|\n"
              << "|\t "<< m_coordsVector( 2, 0 ) << (m_itHasLiterals? "y": " ")<< "\t|";

    m_ui->inputLabel->setText( input );
    m_ui->transformLabel->setText( transformation );
    m_ui->outputLabel->setText( output );
}

void CTransformationHomogeneous::setTransformation()
{
    m_transformation = QTransform( m_transformationMatrix( 0, 0 ), m_transformationMatrix( 0, 1 ), m_transformationMatrix( 0, 2 ),
                                   m_transformationMatrix( 1, 0 ), m_transformationMatrix( 1, 1 ) , m_transformationMatrix( 1, 2 ),
                                   m_transformationMatrix( 2, 0 ), m_transformationMatrix( 2, 1 ) );
}
