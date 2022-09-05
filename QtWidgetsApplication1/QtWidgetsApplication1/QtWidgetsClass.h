#pragma once

#include <QDialog>
#include "ui_QtWidgetsClass.h"

class QtWidgetsClass : public QDialog
{
	Q_OBJECT

public:
	int angle;
	bool do_function;
	QtWidgetsClass(QWidget *parent = nullptr);
	~QtWidgetsClass();

public slots:
	void ok_btn();
	void cancel_btn();

private:
	Ui::QtWidgetsClassClass ui;	
};
