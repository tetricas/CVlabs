#ifndef FRACTALS_WIDGET_H
#define FRACTALS_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class CFractalsWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit CFractalsWidget(QOpenGLWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // FRACTALS_WIDGET_H
