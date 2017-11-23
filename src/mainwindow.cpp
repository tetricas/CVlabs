#include "MainWindow.h"
#include "ui_mainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
}

CMainWindow::~CMainWindow()
{
    delete m_ui;
}
