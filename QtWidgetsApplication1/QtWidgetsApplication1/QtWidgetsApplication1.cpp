#include "QtWidgetsApplication1.h"  //Ĭ�ϴ���
#include "QtWidgetsClass.h"

//������ֻ����һ��
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)  //Ĭ�ϴ���
    : QWidget(parent)  //Ĭ�ϴ���
{
    ui.setupUi(this);  //Ĭ�ϴ���
	dlg = new QtWidgetsClass();  //����һ���´���
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(btn1clicked()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(btn2clicked()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(btn3clicked()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(btn4clicked()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(btn5clicked()));
	connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(show_video()));
	connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(btn7clicked()));
}

QtWidgetsApplication1::~QtWidgetsApplication1()  //Ĭ�ϴ���
{}  //Ĭ�ϴ���

//��ͼ��
void QtWidgetsApplication1::btn1clicked()
{
	//��ȡͼ���ַĿ¼
	filename = QFileDialog::getOpenFileName(this, tr("ѡ��ͼ��"), "", tr("imgaes(*.png *.bmp *.jpg *.tif *.GIF)"));

	//cout << filename.toStdString() << endl;

	//��lineEdit����ʾ����
	ui.lineEdit->setText(filename);
	
	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ȴ�ͼ��"));
		return;
	}

	Mat img;
	img = imread(ui.lineEdit->text().toStdString(), 1);  //.toStdString()�ǽ�QStringתΪStdString

	//��ԭͼ��ת��ΪQImage
	QImage qimg = cvMat2QImage(img);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);

}

//ͼ�������ת
void QtWidgetsApplication1::btn2clicked()
{
	Mat img;

	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ȴ�ͼ��"));
		return;
	}

	img = imread(ui.lineEdit->text().toStdString(), 1);

	dlg->exec();  //�����������д����Ĵ��ڣ�ģ̬��

	if (dlg->do_function)
	{
		img = RotateImg(img, double(dlg->angle));

		QImage qimg = cvMat2QImage(img);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
		ui.label->setScaledContents(true);
	}
}

//ͼ��hsv�仯
void QtWidgetsApplication1::btn3clicked()
{
	Mat img, HSV;

	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ȴ�ͼ��"));
		return;
	}

	img = imread(ui.lineEdit->text().toStdString(), 1);
	cvtColor(img, HSV, COLOR_BGR2HSV);  //��RGBתΪHSV

	QImage qimg = cvMat2QImage(HSV);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);
}

//ͼ����
void QtWidgetsApplication1::btn4clicked()
{
	Mat img = imread(ui.lineEdit->text().toStdString(), 1);

	if (!img.data)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("ͼ��û�д򿪣�"));
		return;
	}

	img = canny(img);

	QImage qimg = cvMat2QImage(img);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);
}

//ͼ���������ģ��
void QtWidgetsApplication1::btn5clicked()
{
	Mat img;

	if (ui.lineEdit->text() == "")
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ȴ�ͼ��"));
		return;
	}

	img = imread(ui.lineEdit->text().toStdString(), 1);

	img = random_g_blur(img, 230000);

	QImage qimg = cvMat2QImage(img);
	ui.label->setPixmap(QPixmap::fromImage(qimg));
	ui.label->setScaledContents(true);
}

//��Ƶ����
void QtWidgetsApplication1::show_video()
{
	filename = QFileDialog::getOpenFileName(this, tr("ѡ����Ƶ"), "", tr("video(*.mp4 *.avi)"));

	if (filename == "")
	{
		return;
	}

	//���ļ��ж�ȡ��Ƶ��������Ϊ0����ʾ��������ͷ�ɼ���Ƶ��
	VideoCapture capture(filename.toStdString());    //��Ƶ·��������
	double rate = capture.get(CAP_PROP_FPS);
	bool stop = false;
	int delay = 1000 / rate;

	//ѭ����ʾÿһ֡
	while (!stop) {
		Mat frame;//����һ��Mat���������ڴ洢ÿһ֡��ͼ��

		//capture >> frame;//��ȡ��ǰ֡
		capture.read(frame);  // ��Ϊ��ȡ��Ƶÿһ֡�ķ�����

		if (!frame.data)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��Ƶ�޷��򿪣�"));
			return;
		}

		QImage qimg = cvMat2QImage(frame);
		ui.label->setPixmap(QPixmap::fromImage(qimg));
		//ui.label->setScaledContents(true);

		if (frame.empty())//������ϣ��˳�
			break;

		//namedWindow("��ȡ��Ƶ֡", WINDOW_AUTOSIZE);  //���ƴ���
		//imshow("��ȡ��Ƶ֡", frame);    //��ʾ��ǰ֡

		 //�ж��Ƿ������ڹرհ�ť
		if (waitKey(delay) >= 0)
			stop = true;
	}

	//system("pause");  linux��������޷�ʹ��
	capture.release();

}

//����Ƿ�ģ��&���ģ���̶�
void QtWidgetsApplication1::btn7clicked()
{
	QStringList fileList = QFileDialog::getOpenFileNames(this, tr("ѡ�����ļ�"), "", tr("imgaes(*.png *.bmp *.jpg *.tif *.GIF)"));

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
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ȴ�ͼ��"));
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


//��Mat ��ʽͼ���Զ�ת��ΪQImage��ʽ
QImage QtWidgetsApplication1::cvMat2QImage(const cv::Mat &mat)
{
	//��Mat ��ʽͼ���Զ�ת��ΪQImage��ʽ
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

//ͼ����ת
Mat QtWidgetsApplication1::RotateImg(Mat image, double angle)
{
	/*
	����ת�Ľ��иĽ�������ͼ����һ�����Σ���ת�����ͼ�����״��һ��ԭͼ�����Ӿ���
	�����Ҫ���¼������ת���ͼ�εĿ�͸�
	*/
	int width = image.cols;
	int height = image.rows;

	double radian = angle * CV_PI / 180.;//�Ƕ�ת��Ϊ����
	double width_rotate = fabs(width*cos(radian)) + fabs(height*sin(radian));
	double height_rotate = fabs(width*sin(radian)) + fabs(height*cos(radian));

	//��ת���� ԭͼ�����ĵ�
	cv::Point2f center((float)width / 2.0, (float)height / 2.0);
	//��ת����
	Mat m1 = cv::getRotationMatrix2D(center, angle, 1.0);
	//m1Ϊ2��3��ͨ����Ϊ1�ľ���
	//�任��������ĵ��൱��ƽ��һ�� ԭͼ������ĵ�����ͼ������ĵ�����λ��
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

	//����һ����srcImage1һ���ľ���
	dstImage.create(srcImage.size(), srcImage.type());
	//��ԭͼ��תΪ�Ҷ�
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	//�˲�(����)
	blur(grayImage, grayImage, Size(3, 3));
	//canny
	Canny(grayImage, edge, 150, 100, 3);

	dstImage = Scalar::all(0);
	srcImage.copyTo(dstImage, edge);

	//ʹ��addWeighted������ʱ��Ҫʱ��ע�⺯����Ҫ�󣬲�Ȼ�ᱨ��
	//�ںϵ�����ͼ��ĳߴ����һ��
	//�����srcImage������dstImage���
	//�����Ҫ���Ҷ�ͼ�񻯵Ļ������뽫grayImage��edge���
	addWeighted(srcImage, 1, dstImage, -0.1, 0.0, dstImage_canny);

	return dstImage_canny;
}

//������ص�ģ��
Mat QtWidgetsApplication1::random_g_blur(Mat image, int nums)
{
	// ����һ��3*3��kernel���
	Mat kernel = (Mat_<float>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1);
	int he = 16;

	for (int n = 0; n < nums; n++)
	{
		int i = rand() % image.rows;//ȡ�������㣬��֤��ͼ���������
		int j = rand() % image.cols;//ȡ�������㣬��֤��ͼ���������
		//cout << i << ", " << j << endl;
		if (i == 0 && j == 0)  //���Ͻ�
		{
			//cout << "���Ͻ�" << i << "," << j << endl;
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
		else if (i == 0 && j != 0 && j != image.cols - 1)  //����
		{
			//cout << "����" << i << "," << j << endl;
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

		else if (i == 0 && j == image.cols - 1)  //���Ͻ�
		{
			//cout << "���Ͻ�" << i << "," << j << endl;
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

		else if (j == 0 && i != 0 && i != image.rows - 1)  //����
		{
			//cout << "����" << i << "," << j << endl;
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

		else if (j == image.cols - 1 && i != 0 && i != image.rows - 1)  //����
		{
			//cout << "����" << i << "," << j << endl;
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

		else if (j == 0 && i == image.rows - 1)  //����
		{
			//cout << "����" << i << "," << j << endl;
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

		else if (i == image.rows - 1 && j != 0 && j != image.cols - 1)  //����
		{
			//cout << "����" << i << "," << j << endl;
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

		else if (i == image.rows - 1 && j == image.cols - 1)  //����
		{
			//cout << "����" << i << "," << j << endl;
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
			//cout << "����" << i << "," << j << endl;
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
