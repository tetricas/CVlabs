#include "Fractals/FractalsWidget.h"

CFractalsWidget::CFractalsWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void CFractalsWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void CFractalsWidget::resizeGL(int w, int h)
{

}

void CFractalsWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
