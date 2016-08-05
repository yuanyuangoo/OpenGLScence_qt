#ifndef MAINWINDOW_H 
#define MAINWINDOW_H 

#include <QMainWindow> 
class QAction;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	QAction *openAction;
};

#endif // MAINWINDOW_H