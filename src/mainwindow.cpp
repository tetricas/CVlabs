#include "MainWindow.h"
#include "ui_mainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_fractalWidget(QSharedPointer<CFractalsWidget>::create())
{
    m_ui->setupUi(this);
    connect(m_ui->fractalsButton, &QPushButton::clicked, [this]()
    {
        m_fractalWidget->show();
    });
}

CMainWindow::~CMainWindow()
{
    delete m_ui;
}
