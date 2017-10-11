#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Transformation/TransformationWidget.h"

namespace Ui {
class MainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

private:
    Ui::MainWindow *m_ui;
};

#endif // MAINWINDOW_H
