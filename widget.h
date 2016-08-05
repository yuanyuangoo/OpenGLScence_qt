#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include "mainwindow.h"

class GLMainWidget;
class MainWindow;

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
	~Widget();
public slots:
	void Syc();
	void SetLocal();
	QPixmap ScreenShot();
	bool Compare(QPixmap pixmap1, QPixmap pixmap2);

private:
    GLMainWidget* glWidget;
	QPixmap localImage;
	bool isLocal;
};

#endif // WIDGET_H
