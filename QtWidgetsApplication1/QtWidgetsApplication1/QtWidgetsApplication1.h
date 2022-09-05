#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidgetsApplication1.h"
#include "QtWidgetsClass.h"

#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class QtWidgetsApplication1 : public QWidget
{
	Q_OBJECT

public:
	QString filename;
	QtWidgetsClass *dlg;

    QtWidgetsApplication1(QWidget *parent = nullptr);  //默认的代码
    ~QtWidgetsApplication1();  //默认的代码

	QImage cvMat2QImage(const cv::Mat &mat);

	Mat RotateImg(Mat image, double angle);

	Mat canny(Mat srcImage);

	Mat random_g_blur(Mat image, int nums = 1000);


public slots:  //接受信息的槽函数
	void btn1clicked();
	void btn2clicked();
	void btn3clicked();
	void btn4clicked();
	void btn5clicked();
	void show_video();
	void btn7clicked();

//以下为默认代码
private:
    Ui::QtWidgetsApplication1Class ui;
};
