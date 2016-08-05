#ifndef GLWIDGET_H
#define GLWIDGET_H
#include "MilkshapeModel.h"
#include <QGLWidget>
class RoamingScenceManager;
class GLMainWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLMainWidget(QWidget *parent = 0);
    ~GLMainWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void wheelEvent(QWheelEvent *e);
	void keyPressEvent(QKeyEvent *e);
public:
	void Syc(float x, float y, float z);
private:
    RoamingScenceManager*manager;
	MilkshapeModel *model;

};

#endif // GLWIDGET_H
