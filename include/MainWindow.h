#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Fractals/FractalsWidget.h"

namespace Ui {
class MainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

private:
    Ui::MainWindow *m_ui;
    QSharedPointer<CFractalsWidget> m_fractalWidget;
};

#endif // MAINWINDOW_H
