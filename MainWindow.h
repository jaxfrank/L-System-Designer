#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>

class Simulator;

class LSystem;
class VariableSequence;
class Variable;

class VariableSequenceModel;

class DialogCreateVariable;
class DialogCreateAxiom;

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

	void on_btnAddAxiom_clicked();

	void on_btnEditAxiom_clicked();

	void on_btnRemoveAxiom_clicked();

	void on_btnSimulate_clicked();

	void on_sbSeed_valueChanged(int value);

	void on_pushButton_clicked();

private:
	Ui::MainWindow* _ui;

	Simulator* _simulator;
	LSystem* _lSystem;
	DialogCreateVariable* _createVariableDialog;
	DialogCreateAxiom* _createAxiomDialog;

	VariableSequence* _currentSystem;
	VariableSequenceModel* _currentSystemModel;

	void editVariable(Variable* variable);

};

#endif // MAINWINDOW_H
