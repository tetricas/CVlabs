#ifndef FRACTALS_WIDGET_H
#define FRACTALS_WIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <array>

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

    std::array<GLfloat, 3> m_cameraPos;
    std::array<GLfloat, 3> m_screenCenter;
    std::array<GLfloat, 3> m_rotateVec;
    std::array<GLfloat, 4> m_light0Pos;
    std::array<GLfloat, 2> m_grounds;
    std::array<GLfloat, 3> m_rotateAngles;
    int m_subdivisions;
    bool m_isInvert;
};

#endif // FRACTALS_WIDGET_H
