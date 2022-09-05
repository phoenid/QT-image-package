#include "QtWidgetsApplication1.h"  //默认代码
#include "QtWidgetsClass.h"

//主函数只运行一次
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)  //默认代码
    : QWidget(parent)  //默认代码
{
    ui.setupUi(this);  //默认代码
	dlg = new QtWidgetsClass();  //创建一个新窗口
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(btn1clicked()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(btn2clicked()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(btn3clicked()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(btn4clicked()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(btn5clicked()));
	connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(show_video()));
	connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(btn7clicked()));
}

QtWidgetsApplication1::~QtWidgetsApplication1()  //默认代码
{}  //默认代码

//打开图像
void QtWidgetsApplication1::btn1clicked()
{
	//获取图像地址目录
	filename = QFileDialog::getOpenFileName(this, tr("选择图像"), "", tr("imgaes(*.png *.bmp *.jpg *.tif *.GIF)"));

	//cout << filename.toStdString() << endl;

	//在lineEdit中显示出来
	ui.lineEdit->setText(filename);
	
	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先打开图像！"));
		return;
	}

	Mat img;
	img = imread(ui.lineEdit->text().toStdString(), 1);  //.toStdString()是将QString转为StdString

	//将原图像转换为QImage
	QImage qimg = cvMat2QImage(img);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);

}

//图像随机翻转
void QtWidgetsApplication1::btn2clicked()
{
	Mat img;

	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先打开图像！"));
		return;
	}

	img = imread(ui.lineEdit->text().toStdString(), 1);

	dlg->exec();  //打开在主函数中创建的窗口（模态）

	if (dlg->do_function)
	{
		img = RotateImg(img, double(dlg->angle));

		QImage qimg = cvMat2QImage(img);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
		ui.label->setScaledContents(true);
	}
}

//图像hsv变化
void QtWidgetsApplication1::btn3clicked()
{
	Mat img, HSV;

	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先打开图像！"));
		return;
	}

	img = imread(ui.lineEdit->text().toStdString(), 1);
	cvtColor(img, HSV, COLOR_BGR2HSV);  //将RGB转为HSV

	QImage qimg = cvMat2QImage(HSV);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);
}

//图像锐化
void QtWidgetsApplication1::btn4clicked()
{
	Mat img = imread(ui.lineEdit->text().toStdString(), 1);

	if (!img.data)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("图像没有打开！"));
		return;
	}

	img = canny(img);

	QImage qimg = cvMat2QImage(img);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);
}

//图像像素随机模糊
void QtWidgetsApplication1::btn5clicked()
{
	Mat img;

	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先打开图像！"));
		return;
	}

	img = imread(ui.lineEdit->text().toStdString(), 1);

	img = random_g_blur(img, 230000);

	QImage qimg = cvMat2QImage(img);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);
}

//视频播放
void QtWidgetsApplication1::show_video()
{
	filename = QFileDialog::getOpenFileName(this, tr("选择视频"), "", tr("video(*.mp4 *.avi)"));

	if (filename == "")
	{
		return;
	}

	//从文件中读取视频。若参数为0，表示调用摄像头采集视频。
	VideoCapture capture(filename.toStdString());    //视频路径及名称
	double rate = capture.get(CAP_PROP_FPS);
	bool stop = false;
	int delay = 1000 / rate;

	//循环显示每一帧
	while (!stop) {
		Mat frame;//定义一个Mat变量，用于存储每一帧的图像

		//capture >> frame;//读取当前帧
		capture.read(frame);  // 此为读取视频每一帧的方法二

		if (!frame.data)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("视频无法打开！"));
			return;
		}

		QImage qimg = cvMat2QImage(frame);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
		//ui.label->setScaledContents(true);

		if (frame.empty())//播放完毕，退出
			break;

		//namedWindow("读取视频帧", WINDOW_AUTOSIZE);  //绘制窗口
		//imshow("读取视频帧", frame);    //显示当前帧

		 //判断是否点击窗口关闭按钮
		if (waitKey(delay) >= 0)
			stop = true;
	}

	//system("pause");  linux里此命令无法使用
	capture.release();

}

//随机是否模糊&随机模糊程度
void QtWidgetsApplication1::btn7clicked()
{
	QStringList fileList = QFileDialog::getOpenFileNames(this, tr("选择多个文件"), "", tr("imgaes(*.png *.bmp *.jpg *.tif *.GIF)"));

	int is_not_blur, kernel;

	int arr[4] = { 3, 5, 7, 9 };

	Mat img, dst;

	for (int i = 0; i < fileList.count(); i++)
	{
		srand(time(0));
		is_not_blur = rand() % 2;
		kernel = arr[rand() % 4];
		
		img = imread(fileList.at(i).toStdString(), 1);

		if (!img.data)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请先打开图像！"));
			return;
		}

		if (is_not_blur == 0)
		{
			GaussianBlur(img, img, Size(kernel, kernel), 10.0, 20.0);
		}

		QImage qimg = cvMat2QImage(img);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
		ui.label->setScaledContents(true);

		waitKey(1000);
	}

}


//将Mat 格式图像自动转换为QImage格式
QImage QtWidgetsApplication1::cvMat2QImage(const cv::Mat &mat)
{
	//将Mat 格式图像自动转换为QImage格式
	switch (mat.type())
	{
		// 8-bit  4 channel
	case CV_8UC4:
	{
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB32);
		return image;
	}

	// 8-bit  3 channel
	case CV_8UC3:
	{
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888);
		return image.rgbSwapped();
	}

	// 8-bit  1 channel
	case CV_8UC1:
	{
		static QVector<QRgb>  sColorTable;
		// only create our color table once
		if (sColorTable.isEmpty())
		{
			sColorTable.resize(256);
			for (int i = 0; i < 256; ++i)
			{
				sColorTable[i] = qRgb(i, i, i);
			}
		}
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Indexed8);
		image.setColorTable(sColorTable);
		return image;
	}
	default:
		qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
		//qWarning() << "cvMatToQImage - cv::Mat image type not handled in switch:" << mat.type();
		break;
	}
	return QImage();
}

//图像旋转
Mat QtWidgetsApplication1::RotateImg(Mat image, double angle)
{
	/*
	对旋转的进行改进，由于图形是一个矩形，旋转后的新图像的形状是一个原图像的外接矩形
	因此需要重新计算出旋转后的图形的宽和高
	*/
	int width = image.cols;
	int height = image.rows;

	double radian = angle * CV_PI / 180.;//角度转换为弧度
	double width_rotate = fabs(width*cos(radian)) + fabs(height*sin(radian));
	double height_rotate = fabs(width*sin(radian)) + fabs(height*cos(radian));

	//旋转中心 原图像中心点
	cv::Point2f center((float)width / 2.0, (float)height / 2.0);
	//旋转矩阵
	Mat m1 = cv::getRotationMatrix2D(center, angle, 1.0);
	//m1为2行3列通道数为1的矩阵
	//变换矩阵的中心点相当于平移一样 原图像的中心点与新图像的中心点的相对位置
	m1.at<double>(0, 2) += (width_rotate - width) / 2.;
	m1.at<double>(1, 2) += (height_rotate - height) / 2.;
	Mat imgOut;
	if (image.channels() == 1)
	{
		cv::warpAffine(image, imgOut, m1, cv::Size(width_rotate, height_rotate), cv::INTER_LINEAR, 0, Scalar(255));
	}
	else if (image.channels() == 3)
	{
		cv::warpAffine(image, imgOut, m1, cv::Size(width_rotate, height_rotate), cv::INTER_LINEAR, 0, Scalar(255, 255, 255));
	}
	return imgOut;
}

//canny
Mat QtWidgetsApplication1::canny(Mat srcImage)
{
	Mat grayImage, dstImage, edge, dstImage_canny;

	//创建一个与srcImage1一样的矩阵
	dstImage.create(srcImage.size(), srcImage.type());
	//将原图像转为灰度
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	//滤波(降噪)
	blur(grayImage, grayImage, Size(3, 3));
	//canny
	Canny(grayImage, edge, 150, 100, 3);

	dstImage = Scalar::all(0);
	srcImage.copyTo(dstImage, edge);

	//使用addWeighted函数的时候，要时刻注意函数的要求，不然会报错
	//融合的两个图像的尺寸必须一样
	//这里的srcImage必须与dstImage配对
	//如果想要出灰度图锐化的话，必须将grayImage与edge配对
	addWeighted(srcImage, 1, dstImage, -0.1, 0.0, dstImage_canny);

	return dstImage_canny;
}

//随机像素点模糊
Mat QtWidgetsApplication1::random_g_blur(Mat image, int nums)
{
	// 定义一个3*3的kernel卷积
	Mat kernel = (Mat_<float>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1);
	int he = 16;

	for (int n = 0; n < nums; n++)
	{
		int i = rand() % image.rows;//取余数运算，保证在图像的列数内
		int j = rand() % image.cols;//取余数运算，保证在图像的行数内
		//cout << i << ", " << j << endl;
		if (i == 0 && j == 0)  //左上角
		{
			//cout << "左上角" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0] =
				(core * kernel.at<float>(1, 1)
					+ (int)image.at<Vec3b>(i, j + 1)[0] * kernel.at<float>(1, 2)
					+ (int)image.at<Vec3b>(i + 1, j)[0] * kernel.at<float>(2, 1)
					+ (int)image.at<Vec3b>(i + 1, j + 1)[0] * kernel.at<float>(2, 2)) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1] = (core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[1] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i + 1, j)[1] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[1] * kernel.at<float>(2, 2)) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2] = (core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[2] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i + 1, j)[2] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[2] * kernel.at<float>(2, 2)) / he;
		}
		else if (i == 0 && j != 0 && j != image.cols - 1)  //上中
		{
			//cout << "上中" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0]
				= ((int)image.at<Vec3b>(i, j - 1)[0] * kernel.at<float>(1, 0)
					+ core * kernel.at<float>(1, 1)
					+ (int)image.at<Vec3b>(i, j + 1)[0] * kernel.at<float>(1, 2)
					+ (int)image.at<Vec3b>(i + 1, j)[0] * kernel.at<float>(2, 1)
					+ (int)image.at<Vec3b>(i + 1, j - 1)[0] * kernel.at<float>(2, 0)
					+ (int)image.at<Vec3b>(i + 1, j + 1)[0] * kernel.at<float>(2, 2)) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1]
				= ((int)image.at<Vec3b>(i, j - 1)[1] * kernel.at<float>(1, 0)
					+ core * kernel.at<float>(1, 1)
					+ (int)image.at<Vec3b>(i, j + 1)[1] * kernel.at<float>(1, 2)
					+ (int)image.at<Vec3b>(i + 1, j)[1] * kernel.at<float>(2, 1)
					+ (int)image.at<Vec3b>(i + 1, j - 1)[1] * kernel.at<float>(2, 0)
					+ (int)image.at<Vec3b>(i + 1, j + 1)[1] * kernel.at<float>(2, 2)) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2]
				= ((int)image.at<Vec3b>(i, j - 1)[2] * kernel.at<float>(1, 0)
					+ core * kernel.at<float>(1, 1)
					+ (int)image.at<Vec3b>(i, j + 1)[2] * kernel.at<float>(1, 2)
					+ (int)image.at<Vec3b>(i + 1, j)[2] * kernel.at<float>(2, 1)
					+ (int)image.at<Vec3b>(i + 1, j - 1)[2] * kernel.at<float>(2, 0)
					+ (int)image.at<Vec3b>(i + 1, j + 1)[2] * kernel.at<float>(2, 2)) / he;
		}

		else if (i == 0 && j == image.cols - 1)  //右上角
		{
			//cout << "右上角" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0]
				= ((int)image.at<Vec3b>(i, j - 1)[0] * kernel.at<float>(1, 0)
					+ core * kernel.at<float>(1, 1)
					+ (int)image.at<Vec3b>(i + 1, j)[0] * kernel.at<float>(2, 1)
					+ (int)image.at<Vec3b>(i + 1, j - 1)[0] * kernel.at<float>(2, 0)) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[0]
				= ((int)image.at<Vec3b>(i, j - 1)[1] * kernel.at<float>(1, 0)
					+ core * kernel.at<float>(1, 1)
					+ (int)image.at<Vec3b>(i + 1, j)[1] * kernel.at<float>(2, 1)
					+ (int)image.at<Vec3b>(i + 1, j - 1)[1] * kernel.at<float>(2, 0)) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2]
				= ((int)image.at<Vec3b>(i, j - 1)[2] * kernel.at<float>(1, 0)
					+ core * kernel.at<float>(1, 1)
					+ (int)image.at<Vec3b>(i + 1, j)[2] * kernel.at<float>(2, 1)
					+ (int)image.at<Vec3b>(i + 1, j - 1)[2] * kernel.at<float>(2, 0)) / he;
		}

		else if (j == 0 && i != 0 && i != image.rows - 1)  //左中
		{
			//cout << "左中" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[0] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[0] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[0] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i + 1, j)[0] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[0] * kernel.at<float>(2, 2)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[1] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[1] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[1] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i + 1, j)[1] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[1] * kernel.at<float>(2, 2)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[2] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[2] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[2] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i + 1, j)[2] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[2] * kernel.at<float>(2, 2)
				) / he;
		}

		else if (j == image.cols - 1 && i != 0 && i != image.rows - 1)  //右中
		{
			//cout << "右中" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i - 1, j)[0] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[0] * kernel.at<float>(0, 0)
				+ (int)image.at<Vec3b>(i, j - 1)[2] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i + 1, j - 1)[0] * kernel.at<float>(2, 0)
				+ (int)image.at<Vec3b>(i + 1, j)[0] * kernel.at<float>(2, 1)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i - 1, j)[1] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[1] * kernel.at<float>(0, 0)
				+ (int)image.at<Vec3b>(i, j - 1)[1] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i + 1, j - 1)[1] * kernel.at<float>(2, 0)
				+ (int)image.at<Vec3b>(i + 1, j)[1] * kernel.at<float>(2, 1)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i - 1, j)[2] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[2] * kernel.at<float>(0, 0)
				+ (int)image.at<Vec3b>(i, j - 1)[2] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i + 1, j - 1)[2] * kernel.at<float>(2, 0)
				+ (int)image.at<Vec3b>(i + 1, j)[2] * kernel.at<float>(2, 1)
				) / he;
		}

		else if (j == 0 && i == image.rows - 1)  //左下
		{
			//cout << "左下" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[0] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[0] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[0] * kernel.at<float>(0, 2)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[1] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[1] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[1] * kernel.at<float>(0, 2)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[2] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[2] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[2] * kernel.at<float>(0, 2)
				) / he;
		}

		else if (i == image.rows - 1 && j != 0 && j != image.cols - 1)  //下中
		{
			//cout << "下中" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[0] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[0] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[0] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i, j - 1)[0] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[0] * kernel.at<float>(0, 0)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[1] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[1] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[1] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i, j - 1)[1] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[1] * kernel.at<float>(0, 0)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[2] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j)[2] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[2] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i, j - 1)[2] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[2] * kernel.at<float>(0, 0)
				) / he;
		}

		else if (i == image.rows - 1 && j == image.cols - 1)  //右下
		{
			//cout << "右下" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i - 1, j)[0] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i, j - 1)[0] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[0] * kernel.at<float>(0, 0)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i - 1, j)[1] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i, j - 1)[1] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[1] * kernel.at<float>(0, 0)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i - 1, j)[2] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i, j - 1)[2] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[2] * kernel.at<float>(0, 0)
				) / he;
		}

		else
		{
			//cout << "其他" << i << "," << j << endl;
			int core = (int)image.at<Vec3b>(i, j)[0];
			image.at<Vec3b>(i, j)[0] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[0] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[0] * kernel.at<float>(0, 0)
				+ (int)image.at<Vec3b>(i, j - 1)[0] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j)[0] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[0] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i + 1, j - 1)[0] * kernel.at<float>(2, 0)
				+ (int)image.at<Vec3b>(i + 1, j)[0] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[0] * kernel.at<float>(2, 2)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[1];
			image.at<Vec3b>(i, j)[1] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[1] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[1] * kernel.at<float>(0, 0)
				+ (int)image.at<Vec3b>(i, j - 1)[1] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j)[1] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[1] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i + 1, j - 1)[1] * kernel.at<float>(2, 0)
				+ (int)image.at<Vec3b>(i + 1, j)[1] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[1] * kernel.at<float>(2, 2)
				) / he;

			core = (int)image.at<Vec3b>(i, j)[2];
			image.at<Vec3b>(i, j)[2] = (
				core * kernel.at<float>(1, 1)
				+ (int)image.at<Vec3b>(i, j + 1)[2] * kernel.at<float>(1, 2)
				+ (int)image.at<Vec3b>(i - 1, j - 1)[2] * kernel.at<float>(0, 0)
				+ (int)image.at<Vec3b>(i, j - 1)[2] * kernel.at<float>(1, 0)
				+ (int)image.at<Vec3b>(i - 1, j)[2] * kernel.at<float>(0, 1)
				+ (int)image.at<Vec3b>(i - 1, j + 1)[2] * kernel.at<float>(0, 2)
				+ (int)image.at<Vec3b>(i + 1, j - 1)[2] * kernel.at<float>(2, 0)
				+ (int)image.at<Vec3b>(i + 1, j)[2] * kernel.at<float>(2, 1)
				+ (int)image.at<Vec3b>(i + 1, j + 1)[2] * kernel.at<float>(2, 2)
				) / he;
		}
	}
	return image;
}
