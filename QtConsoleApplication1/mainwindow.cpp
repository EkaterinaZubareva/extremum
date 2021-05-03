#include "mainwindow.h"
#include "ui_GlobOpt.h"
#include <qgridlayout.h>
#include <qlineedit.h>
#include <vector>
#include "cextremum.h"
#include "baseextremummethod.h"
#include "Piyavsky.h"
#include "Strongin.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setWindowTitle("GlobOpt");
	this->setWindowIcon(QIcon("images.jpg"));


	QGridLayout* lay = new QGridLayout();
	
	ui->scrollArea->setLayout(lay);
	int kol=0;
}
void MainWindow::on_pushButton_clicked()
{ 
	
	kol = ui->lineEdit->text().toInt();// узнаем размерность
	this->createVars(kol);// 
}
/*
	
*/
void MainWindow::createVars(int kol)
{
	for (int i = 0; i < kol; ++i)
	{
		leftLines.push_back(new QLineEdit);
		((QGridLayout*)(ui->scrollArea->layout()))->addWidget(leftLines.back(), i, 0);
		rightLines.push_back(new QLineEdit);
		((QGridLayout*)(ui->scrollArea->layout()))->addWidget(rightLines.back(), i, 1);
	}
	//leftLines[0]->text();
}

void MainWindow::on_start_clicked()
{
	double epsilon = ui->eps->value();//узаем точность
	double r = ui->lipsh->value();//парметр критерия Липшица
	int mon = 0;//
	QString f = ui->function->text();//считываем функцию в формате Qstring
	std::string strstd = f.toStdString();
	auto func = CFunction(strstd);
	func.dim = ui->lineEdit->text().toInt();
	for (int i = 0; i < func.dim; ++i)
	{
		func.addDiaposon(std::pair<double, double>{leftLines[i]->text().toDouble(), rightLines[i]->text().toDouble()});
		}
	//func.addDiaposon(std::pair<double, double>{-5, 5});
	//func.addDiaposon(std::pair<double, double>{0, 10});
	//func.addDiaposon(std::pair<double, double>{-5, 10});
	BaseExtremumMethod* ptr = nullptr;
	QString method = "basic";
	if (ui->scan->isChecked()) {
		ptr = new BaseExtremumMethod;
	}
	if (ui->loma->isChecked()) {
		ptr = new Piyavsky;
	}
	if (ui->strong->isChecked()) {
		ptr = new Strongin;
	}
	auto ext = CExtremum(ptr); //передаем как аргумент указатель на класс с методом
	
	
	//ui->min->setText();
	vectorCoordinat coordinatsMin;
	if (ui->mon1->isChecked()) {
		mon = 1;
	}
	if (ui->mon2->isChecked()) {
		mon = 2;
	}
	coordinatsMin=ext.extremum(func, epsilon, r, mon);
	QString str;
	foreach(double e, coordinatsMin.x)
	{
		str += QString::number(e)+";  ";
		
	}
	ui->best->setText(str);
	//string t = Convert.ToString(coordinatsMin.x);
    ui->min->setText(QString::number(coordinatsMin.z));
	//запускаем скрипт для графиков

	//cout << infoPoint.size();
	ui->kolvo->setText(QString::number(ext.getNumPoints()));
	if (kol == 2) {
		QStringList arguments{ "graphics.py", QString::number(func.dim) };
		QProcess* p = new QProcess;
		p->start("python", arguments);
	}
	else {
			QStringList arguments{ "trisurf3d_demo.py", QString::number(func.dim) };
			QProcess* p = new QProcess;
			p->start("python", arguments);
	}

}

MainWindow::~MainWindow()
{
	delete ui;
}