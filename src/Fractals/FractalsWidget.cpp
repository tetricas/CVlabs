#include "Fractals/FractalsWidget.h"

#include <GL/glu.h>
#include <QTimer>

#define MAX_SUBDIVISION 7

CFractalsWidget::CFractalsWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::DoubleBuffer| QGL::DepthBuffer | QGL::Rgba), parent),
    m_cameraPos({ 0, 0, 9.0 }),
    m_screenCenter({0, 0, -1 }),
    m_rotateVec({ 0, 1, 0}),
    m_light0Pos({ 10, 10, 100, 1 }),
    m_grounds({1, 1000}),
    m_rotateAngles({ 15.0, 45.0, 15.0 }),
    m_subdivisions(1),
    m_isInvert(false)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Animate()));
    timer->start(25);

    // frames and display synchronization
    QGLFormat frmt;
    frmt.setSwapInterval(1);
    setFormat(frmt);
}

void CFractalsWidget::initializeGL()
{
    initializeOpenGLFunctions();
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat aLightPosition[] = {0.0f,0.3f,1.0f,0.0f};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, aLightPosition);
}

void CFractalsWidget::resizeGL(GLint iWidth, GLint iHeight)
{
    glViewport(0, 0, iWidth, iHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)iWidth/iHeight, m_grounds[0], m_grounds[1]);
    glMatrixMode(GL_MODELVIEW);
}

void CFractalsWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(m_cameraPos[0], m_cameraPos[1], m_cameraPos[2],
            m_screenCenter[0], m_screenCenter[1], m_screenCenter[2],
            m_rotateVec[0], m_rotateVec[1], m_rotateVec[2]);
    glLightfv(GL_LIGHT0, GL_POSITION, m_light0Pos.data());

    glRotatef(m_rotateAngles[0], 1, 0, 0);
    glRotatef(m_rotateAngles[1], 0, 1, 0);
    glRotatef(m_rotateAngles[2], 0, 0, 1);

    RenderObject();
}

void CFractalsWidget::DrawCubeFace(GLfloat size, GLfloat *color, GLfloat *specular)
{
    size /= 2.0;
    glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glColor3fv(color);

    glVertex3f(-size,-size,size);
    glVertex3f(size,-size,size);
    glVertex3f(size,size,size);
    glVertex3f(-size,size,size);

    glEnd();
}

void CFractalsWidget::DrawCube(GLfloat size)
{
    //Sides colors(red, green, blue, yellow, cyan, magenta)
    float colors[6][4] = {
        { 1.0, 0.0, 0.0, 1.0 },
        { 0.0, 1.0, 0.0, 1.0 },
        { 0.0, 0.0, 1.0, 1.0 },
        { 0.0, 1.0, 1.0, 1.0 },
        { 1.0, 0.0, 1.0, 1.0 },
        { 1.0, 1.0, 0.0, 1.0 }
    };
    //Reflection coefficient
    float glSpecular[4] = { 0.0, 0.0, 0.0, 0.0 };
    glPushMatrix();

    int c = 0;
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

    glPopMatrix();
}

void CFractalsWidget::BuildSponge(GLfloat size, int step)
{
    int x,y,z;
    glPushMatrix();
    if(step > 0)
    {
        GLfloat delta = size/3.0;

        for(y = -1; y <= 1; y++)
        {
            for(z=-1; z <= 1; z++)
            {
                for(x=-1; x <= 1; x++)
                {
                    if(!m_isInvert)
                    {
                        if((z == 0 && x == 0) || (y == 0 && (x == 0 || z == 0)))
                            continue;
                    } else
                    {
                        if((y!=0 && z!=0) || (y!=0 && z==0 && x!=0) || (y==0 && z!=0 && x!=0))
                            continue;
                    }

                    glPushMatrix();
                    glTranslatef(x*delta,y*delta,z*delta);
                    BuildSponge(delta,step-1);
                    glPopMatrix();
                }
            }
        }
    } else
    {
        DrawCube(size);
    }

    glPopMatrix();
}

void CFractalsWidget::RenderObject()
{
    glPushMatrix();
    BuildSponge(4.0, m_subdivisions);
    glPopMatrix();
}

void CFractalsWidget::Animate()
{
    for(int i = 0; i < 3; i++)
        m_rotateAngles[i] = fmod(m_rotateAngles[i]+1.0f, 360.0f);

    updateGL();
}
