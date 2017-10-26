#include "Transformation/TransformationWidget.h"
#include "ui_transformationwidget.h"

#include <QMessageBox>
#include <QRegExp>
#include <QtMath>
#include <QtDebug>

CTransformationWidget::CTransformationWidget( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::TransformationWidget ),
    m_currentTransformation( ETransformaions::Scale )
{
    m_ui->setupUi(this);
    setupUi();

    m_leftBottom.first = m_topRight.second = 1;     //{{ 0, R }     first - row
    m_leftBottom.second = m_topRight.first = 0;     // { L, 0 }}    second - column
}

CTransformationWidget::~CTransformationWidget()
{
    delete m_ui;
}

void CTransformationWidget::updateSettings( const QString& name )
{
    if( name == QStringLiteral("Scale") )
    {
        m_ui->settingLabel->setText( QStringLiteral( "Scale parameters:" ) );
        m_ui->secondParameter->setVisible( true );
        m_currentTransformation = ETransformaions::Scale;
    }
    else if( name == QStringLiteral("Rotate") )
    {
        m_ui->settingLabel->setText( QStringLiteral( "Angle:" ) );
        m_ui->secondParameter->setVisible( false );
        m_currentTransformation = ETransformaions::Rotate;
    }
    else if( name == QStringLiteral("Move") )
    {
        m_ui->settingLabel->setText( QStringLiteral( "Move parameters:" ) );
        m_ui->secondParameter->setVisible( true );
        m_currentTransformation = ETransformaions::Move;
    }
}

void CTransformationWidget::startProcessing()
{
    if( !checkInput() )
    {
        QMessageBox::about( this, "Input", "Invalid input" );
        return;
    }

    m_inputVector.fill( 0 );
    m_coordsVector.fill( 0 );
    getCoords();
    getParams();

    switch (m_currentTransformation)
    {
    case ETransformaions::Scale:
        scaleProcess();
        break;
    case ETransformaions::Rotate:
        rotateProcess();
        break;
    case ETransformaions::Move:
        moveProcess();
        break;
    default:
        break;
    }

    outputResults();
}

void CTransformationWidget::setupUi()
{
    m_ui->transformationComboBox->addItems( { "Scale", "Rotate", "Move" } );
    connect( m_ui->transformationComboBox, &QComboBox::currentTextChanged,
             this, &CTransformationWidget::updateSettings );

    connect( m_ui->startBtn, &QPushButton::clicked,
             this, &CTransformationWidget::startProcessing );
}

bool CTransformationWidget::checkInput()
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
            !digitReg.exactMatch( m_ui->firstParameter->toPlainText() ) )
        return false;
    if( m_currentTransformation != ETransformaions::Rotate &&
            !digitReg.exactMatch( m_ui->secondParameter->toPlainText() ) )
        return false;

    return true;
}

void CTransformationWidget::getCoords()
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

void CTransformationWidget::getParams()
{
    m_params = QPair<qreal, qreal>( m_ui->firstParameter->toPlainText().toInt(),
                                m_ui->secondParameter->toPlainText().toInt() );
}

void CTransformationWidget::scaleProcess()
{
    m_transformationMatrix.fill( 0 );
    m_transformationMatrix( 0, 0 ) = m_params.first;
    m_transformationMatrix( 1, 1 ) = m_params.second;

    m_coordsVector = m_transformationMatrix * m_coordsVector;
}

void CTransformationWidget::rotateProcess()
{
    m_transformationMatrix( 0, 0 ) = m_transformationMatrix( 1, 1 ) = qCos( m_params.first );
    m_transformationMatrix( 0, 1 ) = m_transformationMatrix( 1, 0 ) = qSin( m_params.first );

    if( m_params.first < 0 )
        m_transformationMatrix( m_leftBottom.first, m_leftBottom.second ) *= -1;
    else
        m_transformationMatrix( m_topRight.first, m_topRight.second ) *= -1;

    m_coordsVector = m_transformationMatrix * m_coordsVector;
}

void CTransformationWidget::moveProcess()
{
    m_coordsVector( 0, 0 ) += m_params.first;
    m_coordsVector( 1, 0 ) += m_params.second;
    m_transformationMatrix.fill( 0 );
}

void CTransformationWidget::outputResults()
{
    QString input, transformation, output;
    QTextStream streamIn(&input), streamTrans(&transformation), streamOut(&output);

    streamIn << "Input vector: \n"
             << "|\t"<< m_inputVector( 0, 0 ) << "\t|\n"
             << "|\t"<< m_inputVector( 1, 0 ) << "\t|";

    streamTrans << "Transformation matrix: \n"
                << "|\t"<< m_transformationMatrix( 0, 0 )<< ",\t"<< m_transformationMatrix( 0, 1 ) << "\t|\n"
                << "|\t"<< m_transformationMatrix( 1, 0 )<< ",\t"<< m_transformationMatrix( 1, 1 ) << "\t|";

    streamOut << "Resul vector: \n"
              << "|\t"<< m_coordsVector( 0, 0 ) << "\t|\n"
              << "|\t"<< m_coordsVector( 1, 0 ) << "\t|";

    m_ui->inputLabel->setText( input );
    m_ui->transformLabel->setText( transformation );
    m_ui->outputLabel->setText( output );
}
