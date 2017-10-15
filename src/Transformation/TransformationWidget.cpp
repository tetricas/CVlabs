#include "Transformation/TransformationWidget.h"
#include "ui_transformationwidget.h"

#include <QMessageBox>
#include <QRegExp>

CTransformationWidget::CTransformationWidget( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::TransformationWidget ),
    m_currentTransformation( ETransformaions::Scale )
{
    m_ui->setupUi(this);
    setupUi();
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

    getCoords();

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
            !digitReg.exactMatch( m_ui->firstParameter->toPlainText() ) ||
            !digitReg.exactMatch( m_ui->secondParameter->toPlainText() ) )
        return false;

    return true;
}

void CTransformationWidget::getCoords()
{
    if( !m_itHasLiterals )
    {
        m_coords.setX( m_ui->xCoordEdit->toPlainText().toInt() );
        m_coords.setY( m_ui->yCoordEdit->toPlainText().toInt() );
    }
    else
    {
        QRegExp digitReg("(\\d+|-\\d+)");

        digitReg.indexIn( m_ui->xCoordEdit->toPlainText() );
        m_coords.setX( digitReg.cap(1).toInt() );

        digitReg.indexIn( m_ui->yCoordEdit->toPlainText() );
        m_coords.setY( digitReg.cap(1).toInt() );
    }
}

void CTransformationWidget::scaleProcess()
{

}

void CTransformationWidget::rotateProcess()
{

}

void CTransformationWidget::moveProcess()
{

}
