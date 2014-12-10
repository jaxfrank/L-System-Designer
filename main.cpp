#include "MainWindow.h"
#include <QApplication>

#include <random>
#include <map>
#include <vector>

#include <QDebug>
#include <QString>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
