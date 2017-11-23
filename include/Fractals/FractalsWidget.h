#ifndef FRACTALS_WIDGET_H
#define FRACTALS_WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class CFractalsWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit CFractalsWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(GLint iWidth, GLint iHeight) override;
    void paintGL() override;

private:
    void DrawCubeFace(GLfloat size, GLfloat* color, GLfloat* specular);
    void DrawCube(GLfloat size);
    void BuildSponge(GLfloat size, int step);
    void RenderObject();

    //Положение камеры
    GLfloat eye[3] = { 0, 0, 9.0 };
    //Положение центра экрана
    GLfloat center[3] = {0, 0, -1 };
    //Координаты вектора задающего поворот сцены
    GLfloat up[3] = { 0, 1, 0};
    //Положение освещения
    GLfloat light0Pos[4] = { 10, 10, 100, 1 };
    //Передний и задний план
    GLfloat planes[2] = {1, 1000};
    //Ширина и высота
    int width= 640, height=480;
    //Флаг отвечающий за автоматическое вращение
    bool autoRotate = false;
    //Переменная для сохранения предыдущего времени вызова
    unsigned long last_idle_time;
    //Массив углов поворота текущего положения куба
    GLfloat rot[3] = { 15.0, 45.0, 15.0 };
    //Текущий уровень вложенности куба
    int subdivisions = 0;
    //Флаг отвечающий за инвертирование.
    bool invert = false;
    //Состояние кнопок мыши
    bool mouseButtonDown[3] = { false };
    //Координаты щелчка мышью
    int mouseButtonClick[3][2] = { { 0, 0 }, {0, 0}, {0, 0} };
};

#endif // FRACTALS_WIDGET_H
