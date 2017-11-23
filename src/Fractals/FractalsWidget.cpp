#include "Fractals/FractalsWidget.h"

#define MAX_SUBDIVISION 7

CFractalsWidget::CFractalsWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void CFractalsWidget::initializeGL()
{
    initializeOpenGLFunctions();
    last_idle_time = clock();
    glEnable(GL_DEPTH_TEST);
    //Сравнение "если меньше"
    glDepthFunc(GL_LESS);
    //Включаем тени путем интерполяции
    glShadeModel(GL_SMOOTH);
    //Включаем освещение
    glEnable(GL_LIGHTING);
    //Включаем 0 точку освещения
    glEnable(GL_LIGHT0);
}

void CFractalsWidget::resizeGL(GLint iWidth, GLint iHeight)
{
    //Увеличиваем размер области просмотра
    glViewport(0, 0, iWidth, iHeight);
    //Загружаем поективную матрицу
    glMatrixMode(GL_PROJECTION);
    //Делаем ее единичной
    glLoadIdentity();
    //Задаем перспективу
    //gluPerspective(45.0, (float)iWidth/iHeight, planes[0], planes[1]);
    //Загружаем объектно-видовую матрицу
    glMatrixMode(GL_MODELVIEW);
    //Обновляем переменные
    width = iWidth;
    height = iHeight;
}

void CFractalsWidget::paintGL()
{
    //Очищаем изображение
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Загружаем единичную матрицу
    glLoadIdentity();
    //Переводим внешнюю систему координат в систему координат камеры
    //gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
    //Добавляем освещение
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    //Поворачиваем сцену по данным из rot[]
    glRotatef(rot[0], 1, 0, 0);
    glRotatef(rot[1], 0, 1, 0);
    glRotatef(rot[2], 0, 0, 1);
    //Вызываем рисование фрактала
    RenderObject();
}

void CFractalsWidget::DrawCubeFace(GLfloat size, GLfloat *color, GLfloat *specular)
{
    size /= 2.0;
    //Начинаем рисование в режиме четырехугольников
    glBegin(GL_QUADS);
    //Задаем коеффициент рассеивания света грани
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    //Задаем коеффициент отражения света грани
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    //Задаем цвет грани
    glColor3fv(color);
    //Рисуем прямоугольник по точкам
    glVertex3f(-size,-size,size);
    glVertex3f(size,-size,size);
    glVertex3f(size,size,size);
    glVertex3f(-size,size,size);
    //Заканчиваем рисование
    glEnd();
}

void CFractalsWidget::DrawCube(GLfloat size)
{
    //Зададим цвета граней(red, green, blue, yellow, cyan, magenta)
    float colors[6][4] = {
        { 1.0, 0.0, 0.0, 1.0 },
        { 0.0, 1.0, 0.0, 1.0 },
        { 0.0, 0.0, 1.0, 1.0 },
        { 0.0, 1.0, 1.0, 1.0 },
        { 1.0, 0.0, 1.0, 1.0 },
        { 1.0, 1.0, 0.0, 1.0 }
    };
    //Зададим коеффициент отражения
    float glSpecular[4] = { 0.0, 0.0, 0.0, 0.0 };
    //Сохраняем матрицу
    glPushMatrix();
    //Переменная-счетчик, будет увеличиватся для выбора цвета
    int c = 0;
    //Рисуем поверхность, поворачиваем, рисуем следующую..
    DrawCubeFace(size, colors[c++], glSpecular);
    glRotatef(90, 1, 0, 0);
    DrawCubeFace(size, colors[c++], glSpecular);
    glRotatef(90, 1, 0, 0);
    DrawCubeFace(size, colors[c++], glSpecular);
    glRotatef(90, 1, 0, 0);
    DrawCubeFace(size, colors[c++], glSpecular);
    glRotatef(90, 0, 1, 0);
    DrawCubeFace(size, colors[c++], glSpecular);
    glRotatef(180, 0, 1, 0);
    DrawCubeFace(size, colors[c++], glSpecular);
    //Возвращаем матрицу
    glPopMatrix();
}

void CFractalsWidget::BuildSponge(GLfloat size, int step)
{
    int x,y,z;
    //Сохраняем матрицу
    glPushMatrix();
    //Проверяем уровень вложенности
    if(step > 0) {
        //Если больше 0, то нужно делить куб на части
        //Делим текущий размер на 3
        GLfloat delta = size/3.0;

        //Обычный куб
        //Нижняя сторона
        //{-1, -1, -1} {0, -1, -1} {1, -1, -1}	задняя часть
        //{-1, -1, 0}				{1, -1, 0}	середина
        //{-1, -1, 1} {0, -1, 1} {1, -1, 1}		передняя часть

        //Середина
        //{-1, 0, -1}		{1, 0, -1}			задняя часть
        //										середина
        //{-1, 0, 1}		{1, 0, 1}			передняя часть

        //Верхняя сторона
        //{-1, 1, -1} {0, 1, -1} {1, 1, -1}		задняя часть
        //{-1, 1, 0}			{1, -1, 0}		середина
        //{-1, 1, 1} {0, 1, 1} {1, 1, 1}		передняя часть
        //
        //Инвертированный куб
        //Нижняя сторона y=-1
        //										задняя часть z=-1
        //			{0, -1, 0}					середина z=0
        //										передняя часть z=1
        //Середина y=0
        //			{0, 0, -1}					задняя часть z=-1
        //{-1, 0, 0} {0, 0, 0} {1, 0, 0}		середина z=0
        //			{0, 0, 1}					передняя часть z=1
        //Верхняя сторона y=1
        //										задняя часть z=-1
        //			{0, 1, 0}					середина z=0
        //										передняя часть z=1

        //Цикл по сторонам
        for(y = -1; y <= 1; y++) {
            //Цикл из задней части к передней
            for(z=-1; z <= 1; z++) {
                //Цикл с лева на право
                for(x=-1; x <= 1; x++) {
                    //Проверяем нужно ли рисовать. Два больших условия которые проверяют
                    //для инвертированного и неинвертированного куба, если рисовать не нужно
                    //переходим на следующий шаг цикла
                    if(!invert){
                        if((z == 0 && x == 0) || (y == 0 && (x == 0 || z == 0))) continue;
                    } else {
                        if((y!=0 && z!=0) || (y!=0 && z==0 && x!=0) || (y==0 && z!=0 && x!=0)) continue;
                    }
                    //Сохраняем текущую матрицу
                    glPushMatrix();
                    //Переносим систему координат для подкуба
                    glTranslatef(x*delta,y*delta,z*delta);
                    //Рекурсивно вызываем для следующего шага
                    BuildSponge(delta,step-1);
                    //Возвращаем матрицу
                    glPopMatrix();
                }
            }
        }
    } else {
        //Если шаг = 0, значит вложений больше нет, просто рисуем куб
        DrawCube(size);
    }
    //Возвращаем матрицу
    glPopMatrix();
}

void CFractalsWidget::RenderObject()
{
    //Сохраняем матрицу
    glPushMatrix();
    //Рисуем губку максимального размера 4.0 и заданным уровнем вложенности
    BuildSponge(4.0, subdivisions);
    //Возвращаем сохраненную матрицу
    glPopMatrix();
}
