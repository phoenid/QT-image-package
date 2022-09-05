#include "QtWidgetsClass.h"

QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(ok_btn()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(cancel_btn()));
}

QtWidgetsClass::~QtWidgetsClass()
{}

void QtWidgetsClass::ok_btn()
{
	angle = ui.lineEdit->text().toInt();  //将输入的角度转为int赋值给angle
	do_function = true;
	this->close();
}

void QtWidgetsClass::cancel_btn()
{
	do_function = false;
	this->close();
}