#pragma once

#include <QWidget>
#include "ui_RigestUser.h"

class RigestUser : public QWidget
{
	Q_OBJECT

public:
	RigestUser(QWidget *parent = Q_NULLPTR);
	~RigestUser();

private:
	Ui::RigestUser ui;
};
