#include"Dependencies/glew/glew.h"
#include"Dependencies/Freeglut/freeglut.h"

#include"GLMainWidget.h"
#include"RoamingScenceManager.h"

#include<QMouseEvent>
#include<QWheelEvent>
#include<QDebug>

GLMainWidget::GLMainWidget(QWidget *parent) :
    QGLWidget(parent)
{
	this->setFocusPolicy(Qt::StrongFocus);
    manager=new RoamingScenceManager();
}

GLMainWidget::~GLMainWidget()
{
    delete manager;
	delete model;
}



void GLMainWidget::initializeGL()
{
    manager->init();
	model = new MilkshapeModel();

	if (!model->loadModelData("Data\\Scooter\\Scooter.ms3d"))
	{
		exit(-1);
	}
}

void GLMainWidget::resizeGL(int w, int h)
{
    glViewport(0,-(w-h)/2,w,w);
}
void GLMainWidget::paintGL()
{
    manager->render();
 	model->draw();

}

void GLMainWidget::mousePressEvent(QMouseEvent *e)
{
	manager->getInitPos(e->x(), e->y());
}

void GLMainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton)
    {
        if(e->modifiers()==Qt::CTRL)
        {
            manager->executeTranslateOperation(e->x(),e->y());
        }
        else
        {
            manager->executeRotateOperation(e->x(),e->y());
        }
    }
    updateGL();
}

void GLMainWidget::wheelEvent(QWheelEvent *e)
{
    if(e->delta()>=0)
    {
        manager->executeScaleOperation(-0.1);
    }else
    {
        manager->executeScaleOperation(0.1);
    }
    updateGL();
}

void GLMainWidget::keyPressEvent(QKeyEvent * e)
{
	if (e->key()==Qt::Key_Escape)
	{
		exit(-1);
	}
}

void GLMainWidget::Syc(float x, float y, float z)
{
	model->Syc(x, y, z);
}
