#ifndef FRACTALS_WIDGET_H
#define FRACTALS_WIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>

class CFractalsWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit CFractalsWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(GLint iWidth, GLint iHeight) override;
    void paintGL() override;

private slots:
    void Animate();

private:
    void DrawCubeFace(GLfloat size, GLfloat* color, GLfloat* specular);
    void DrawCube(GLfloat size);
    void BuildSponge(GLfloat size, int step);
    void RenderObject();
};

#endif // FRACTALS_WIDGET_H
