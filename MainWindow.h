#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>

class LSystem;
class DialogCreateVariable;
class Variable;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	LSystem* getLSystem();

private slots:
	void on_btnAddVariable_clicked();

	void on_btnRemoveVariable_clicked();

	void on_btnEditVariable_clicked();

	void on_variableListView_doubleClicked(const QModelIndex &index);

private:
	Ui::MainWindow* _ui;

	LSystem* _lSystem;
	DialogCreateVariable* _createVariableDialog;

	void editVariable(Variable* variable);

};

#endif // MAINWINDOW_H
