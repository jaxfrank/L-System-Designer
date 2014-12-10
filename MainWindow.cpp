#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QString>
#include <QDebug>

#include "VariableSequence.h"
#include "Variable.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow() {
	delete ui;
}
