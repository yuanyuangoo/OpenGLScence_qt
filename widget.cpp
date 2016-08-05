#include "widget.h"
#include"GLMainWidget.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include<QPixmap>
#include<qapplication.h>
#include <QDesktopWidget>
#include <opencv2/opencv.hpp>

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
{
	QMenuBar *menuBar = new QMenuBar;
	QMenu *menuWindow = menuBar->addMenu(tr("&Action"));

	QAction *Syc1 = new QAction(menuWindow);
	QAction *SetLocal1 = new QAction(menuWindow);


	Syc1->setText(tr("Syc"));
	SetLocal1->setText(tr("SetLocal"));


	menuWindow->addAction(Syc1);
	menuWindow->addAction(SetLocal1);

	connect(Syc1, &QAction::triggered, this, &Widget::Syc);
	connect(SetLocal1, &QAction::triggered, this, &Widget::SetLocal);


	setMenuBar(menuBar);

	resize(QSize(800.f, 600.f));
//    showMaximized();
    glWidget=new GLMainWidget();
    setCentralWidget(glWidget);
	isLocal = false;
}
Widget::~Widget()
{
    delete glWidget;
}
void convertQImageToMat(QImage &img_qt, cv::Mat_<cv::Vec3b>& img_cv)
{

	img_cv.create(img_qt.height(), img_qt.width());

	img_qt.convertToFormat(QImage::Format_RGB32);

	int lineNum = 0;

	int height = img_qt.height();

	int width = img_qt.width();

	uchar *imgBits = img_qt.bits();

	for (int i = 0; i < height; i++)
	{
		lineNum = i* width * 4;
		for (int j = 0; j < width; j++)
		{
			img_cv(i, j)[2] = imgBits[lineNum + j * 4 + 2];
			img_cv(i, j)[1] = imgBits[lineNum + j * 4 + 1];
			img_cv(i, j)[0] = imgBits[lineNum + j * 4 + 0];
		}
	}
}
QPixmap Widget::ScreenShot()
{
	return QPixmap::grabWindow(glWidget->winId());
}



cv::Mat convertQPixmapToMat(QPixmap img_qt, cv::Mat_<cv::Vec3b> img_cv)
{
	img_qt.save("tmp.png", "png");
	img_cv = cv::imread("tmp.png");
	return img_cv;
}

void Widget::SetLocal()
{
	localImage= QPixmap::grabWindow(glWidget->winId());
	isLocal = true;
}

void Widget::Syc()
{
	bool endsyc = false;
	QPixmap Image;
	for (int x = 0; x < 180 && !endsyc; x++)
		for (int y = 0; y < 180 && !endsyc; y++)
			for (int z = 0; z < 180 && !endsyc; z++)
			{
				glWidget->Syc(x, y, z);
				glWidget->show();
				Image = QPixmap::grabWindow(glWidget->winId());
				endsyc = Compare(Image, localImage);
			}
	if (!endsyc)
	{
		QMessageBox::critical(NULL, "critical", "Critical", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}
bool Widget::Compare(QPixmap pixmap1, QPixmap pixmap2)
{
	if (!isLocal) 
	{
		QMessageBox::critical(NULL, "No Local", "No Local", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return false;
	}


	if (pixmap1.size() != pixmap2.size())
	{
		return false;
	}
	cv::Mat img1, img2;
	img1 = convertQPixmapToMat(pixmap1, img1);
	img2 = convertQPixmapToMat(pixmap2, img2);

	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			cv::Vec3b intensity1 = img1.at<cv::Vec3b>(i, j);
			uchar blue1 = intensity1.val[0];
			uchar green1 = intensity1.val[1];
			uchar red1 = intensity1.val[2];

			cv::Vec3b intensity2 = img2.at<cv::Vec3b>(i, j);
			uchar blue2 = intensity2.val[0];
			uchar green2 = intensity2.val[1];
			uchar red2 = intensity2.val[2];

			if (blue1 != blue2 || green2 != green1 || red2 != red1)
			{
				return false;
			}
		}
	}
	return true;
}