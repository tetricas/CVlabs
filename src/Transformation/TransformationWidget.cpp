#include "Transformation/TransformationWidget.h"
#include "ui_transformationwidget.h"

#include <QMessageBox>
#include <QRegExp>
#include <QtMath>
#include <QtDebug>

CTransformationWidget::CTransformationWidget( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::TransformationWidget ),
    m_hasResults( false ),
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
    if( !checkHomogeneous() )
    {
        QMessageBox::about( this, "Input", "Invalid input: H can not be equal 0!" );
        return;
    }

    if( m_transformation.isNull() )
    {
        QMessageBox::about( this, "Error", "Something went wrong!" );
        return;
    }

    if( !m_transformation->checkInput( m_currentTransformation != ETransformaions::Rotate ) )
    {
        QMessageBox::about( this, "Input", "Invalid input" );
        return;
    }

    m_transformation->getCoords();
    m_transformation->getParams();

    switch (m_currentTransformation)
    {
    case ETransformaions::Scale:
        m_transformation->scaleProcess();
        break;
    case ETransformaions::Rotate:
        m_transformation->rotateProcess();
        break;
    case ETransformaions::Move:
        m_transformation->moveProcess();
        break;
    default:
        break;
    }

    m_transformation->outputResults();
    m_hasResults = true;
}

void CTransformationWidget::visualize()
{
    if( !m_hasResults )
        return;

    m_transformation->setTransformation();
    m_ui->resultLabel->setPixmap( QPixmap(":/images/test.jpg").transformed(m_transform) );
}

void CTransformationWidget::setupUi()
{
    m_ui->transformationComboBox->addItems( { "Scale", "Rotate", "Move" } );
    connect( m_ui->transformationComboBox, &QComboBox::currentTextChanged,
             this, &CTransformationWidget::updateSettings );

    connect( m_ui->startBtn, &QPushButton::clicked, this, &CTransformationWidget::startProcessing );
    connect( m_ui->visualizeBtn, &QPushButton::clicked, this, &CTransformationWidget::visualize );

    m_ui->testLabel->setPixmap( QPixmap(":/images/test.jpg") );
}

bool CTransformationWidget::checkHomogeneous()
{
    int hCoeff = m_ui->zCoordEdit->toPlainText().toInt();

    m_transformation.reset();
    if( hCoeff == 0 )
        return false;
    else if( hCoeff != 1 )
        m_transformation = QSharedPointer<CTransformationHomogeneous>::create(m_ui, m_transform, hCoeff);
    else
        m_transformation = QSharedPointer<CTransformationNormal>::create(m_ui, m_transform);

    return true;
}
