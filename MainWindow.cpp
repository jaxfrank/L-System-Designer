#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QModelIndex>

#include "LSystem.h"
#include "Variable.h"
#include "VariableSequence.h"
#include "VariableSequenceModel.h"
#include "VariableSequenceListModel.h"
#include "ProductionTableModel.h"

#include "DialogCreateVariable.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	_ui(new Ui::MainWindow),
	_lSystem(new LSystem(this)),
	_createVariableDialog(nullptr)
{
	_ui->setupUi(this);
	_ui->variableListView->setModel(_lSystem->getVariableModel());
	_ui->axiomListView->setModel(new VariableSequenceListModel(_lSystem->getAxioms()));
}

MainWindow::~MainWindow() {
	delete _ui;
}

void MainWindow::on_btnAddVariable_clicked() {
	if(!_createVariableDialog)
		_createVariableDialog = new DialogCreateVariable(_lSystem, this);
	_createVariableDialog->setMode(DialogCreateVariable::CREATE);
	_createVariableDialog->setVariable(new Variable);
	_createVariableDialog->show();
}

void MainWindow::on_btnRemoveVariable_clicked() {
	QList<int> indices;
	foreach(const QModelIndex& index, _ui->variableListView->selectionModel()->selectedIndexes()) {
		indices.push_back(index.row());
	}
	qSort(indices);
	for(int i = indices.length() - 1; i >= 0; i--) {
		_ui->variableListView->model()->removeRow(indices.at(i));
	}
}

void MainWindow::on_btnEditVariable_clicked() {
	QModelIndexList indexes = _ui->variableListView->selectionModel()->selectedIndexes();
	if(indexes.length() > 0) {
		editVariable((Variable*)_ui->variableListView->model()->data(indexes[0], Qt::EditRole).value<void*>());
	}
}

void MainWindow::on_variableListView_doubleClicked(const QModelIndex &index) {
	editVariable((Variable*)_ui->variableListView->model()->data(index, Qt::EditRole).value<void*>());
}

void MainWindow::editVariable(Variable* variable) {
	_createVariableDialog->setVariable(variable);
	_createVariableDialog->setMode(DialogCreateVariable::EDIT);
	_createVariableDialog->show();
}
