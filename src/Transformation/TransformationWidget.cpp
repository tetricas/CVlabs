#include "Transformation/TransformationWidget.h"
#include "ui_transformationwidget.h"

#include "QMessageBox"

CTransformationWidget::CTransformationWidget( QWidget *parent ) :
    QWidget( parent ),
    m_ui( new Ui::TransformationWidget )
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
    }
    else if( name == QStringLiteral("Rotate") )
    {
        m_ui->settingLabel->setText( QStringLiteral( "Angle:" ) );
        m_ui->secondParameter->setVisible( false );
    }
    else if( name == QStringLiteral("Move") )
    {
        m_ui->settingLabel->setText( QStringLiteral( "Move parameters:" ) );
        m_ui->secondParameter->setVisible( true );
    }
}

void CTransformationWidget::setupUi()
{
    m_ui->transformationComboBox->addItems( { "Scale", "Rotate", "Move" } );
    connect( m_ui->transformationComboBox, &QComboBox::currentTextChanged,
             this, &CTransformationWidget::updateSettings );
}
