#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QModelIndex>

#include "Simulator.h"
#include "VariableSequenceRenderer.h"

#include "LSystem.h"
#include "Variable.h"
#include "VariableSequence.h"
#include "VariableSequenceModel.h"
#include "VariableSequenceListModel.h"
#include "ProductionTableModel.h"

#include "DialogCreateVariable.h"
#include "DialogCreateAxiom.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	_ui(new Ui::MainWindow),
	_simulator(new Simulator()),
	_lSystem(new LSystem(this)),
	_createVariableDialog(nullptr),
	_createAxiomDialog(nullptr),
	_currentSystem(nullptr),
	_currentSystemModel(nullptr),
	_renderer(new VariableSequenceRenderer())
{
	_ui->setupUi(this);
	_ui->variableListView->setModel(_lSystem->getVariableModel());
	_ui->axiomListView->setModel(_lSystem->getAxiomModel());

	_simulator->setLSystem(_lSystem);

	_ui->lSystemGraphicsView->setScene(_renderer->getScene());
}

MainWindow::~MainWindow() {
	delete _ui;
	delete _renderer;
	if(_currentSystemModel) delete _currentSystemModel;
	if(_currentSystem) delete _currentSystem;
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
	if(!_createVariableDialog) {
		_createVariableDialog = new DialogCreateVariable(_lSystem, this);
	}

	_createVariableDialog->setVariable(variable);
	_createVariableDialog->setMode(DialogCreateVariable::EDIT);
	_createVariableDialog->show();
}

void MainWindow::on_btnAddAxiom_clicked() {
	if(!_createAxiomDialog)
		_createAxiomDialog = new DialogCreateAxiom(_lSystem, this);

	_createAxiomDialog->setAxiom(new VariableSequenceModel(new VariableSequence));
	_createAxiomDialog->setMode(DialogCreateAxiom::CREATE);
	_createAxiomDialog->show();
}

void MainWindow::on_btnEditAxiom_clicked() {
	if(!_createAxiomDialog)
		_createAxiomDialog = new DialogCreateAxiom(_lSystem, this);

	QModelIndexList selectedIndices = _ui->axiomListView->selectionModel()->selectedIndexes();
	if(selectedIndices.length() > 0) {
		QModelIndex firstIndex = selectedIndices.at(0);
		QModelIndex choosen = _ui->axiomListView->model()->index(firstIndex.row(), 0, QModelIndex());
		_createAxiomDialog->setAxiom((VariableSequenceModel*)_ui->axiomListView->model()->data(choosen, Qt::UserRole).value<void*>());
		_createAxiomDialog->setMode(DialogCreateAxiom::Mode::EDIT);
		_createAxiomDialog->show();
	}
}

void MainWindow::on_btnRemoveAxiom_clicked() {
	foreach(QModelIndex index, _ui->axiomListView->selectionModel()->selectedRows()) {
		_ui->axiomListView->model()->removeRow(index.row());
	}
}

void MainWindow::on_btnSimulate_clicked() {
	if(_currentSystemModel) {
		_ui->simulatedListView->setModel(nullptr);
		delete _currentSystemModel;
	}
	if(_currentSystem) delete _currentSystem;

	int recurseLevel = _ui->sbRecurseLevel->value();
	VariableSequence* result = _simulator->simulate(recurseLevel);
	if(!result) return;
	_currentSystem = result;
	_currentSystemModel = _currentSystem->getModel();
	_ui->simulatedListView->setModel(_currentSystemModel);

	_renderer->setSequence(result);
	_renderer->evaluateSequence();
}

void MainWindow::on_sbSeed_valueChanged(int value) {
	_simulator->setSeed(value);
}

void MainWindow::on_pushButton_clicked() {
   int seed = (int)_simulator->generateSeed();
   qDebug() << seed;
   _ui->sbSeed->setValue(seed);
}
