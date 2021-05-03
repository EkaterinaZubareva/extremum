#include "mainwindow.h"
#include <QApplication>
#include "cfunction.h"
#include "cextremum.h"
#include "baseextremummethod.h"
#include <utility>
#include <QProcess>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	    MainWindow w;
	    w.show();
		return a.exec();
}
