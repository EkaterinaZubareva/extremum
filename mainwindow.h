#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlineedit.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	public slots:
		void createVars(int kol);
		
private:
    Ui::MainWindow *ui;
	std::vector<QLineEdit*> leftLines;
	std::vector<QLineEdit*> rightLines;
	int kol;
//	void functionToFile(CFunction &function);

private slots:
	void on_pushButton_clicked();
	void on_start_clicked();
	
};

#endif // MAINWINDOW_H
