#include <QAction> 
#include <QMenu> 
#include <QMenuBar> 
#include <QKeySequence> 
#include <QToolBar> 
#include "mainwindow.h" 
#include "widget.h"

MainWindow::MainWindow(QWidget *parent)
{
	openAction = new QAction(tr("&Open"), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open a file."));

	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction);

	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction);

	if (!centralWidget())
		setCentralWidget(new Widget(this));

}

MainWindow::~MainWindow()
{

}