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
    if( checkHomogeneous() )
    {
        m_transformation = QSharedPointer<CTransformationHomogeneous>::create(m_ui);
        qDebug() << "CTransformationHomogeneous";
    }
    else
    {
        m_transformation = QSharedPointer<CTransformationNormal>::create(m_ui);
        qDebug() << "CTransformationNormal";
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
}

void CTransformationWidget::setupUi()
{
    m_ui->transformationComboBox->addItems( { "Scale", "Rotate", "Move" } );
    connect( m_ui->transformationComboBox, &QComboBox::currentTextChanged,
             this, &CTransformationWidget::updateSettings );

    connect( m_ui->startBtn, &QPushButton::clicked,
             this, &CTransformationWidget::startProcessing );
}

bool CTransformationWidget::checkHomogeneous()
{
    return m_ui->zCoordEdit->toPlainText().toInt() != 1;
}
