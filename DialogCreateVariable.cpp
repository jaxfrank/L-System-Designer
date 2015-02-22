#include "DialogCreateVariable.h"
#include "ui_DialogCreateVariable.h"

#include "Variable.h"
#include "ProductionTableModel.h"
#include "Production.h"
#include "MainWindow.h"
#include "LSystem.h"

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QDebug>

DialogCreateVariable::DialogCreateVariable(LSystem* lSystem, QWidget* parent) :
	QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint),
	_ui(new Ui::DialogCreateVariable),
	_lSystem(lSystem),
	_variable(nullptr),
	_variableModel(lSystem->getVariableModel()),
	_itemDelegate(new SpinBoxDelegate(this)),
	_currentMode(CREATE),
	_currentProductionModel(nullptr)
{
	_ui->setupUi(this);

	_ui->variableListView->setModel(_variableModel);
	_ui->productionsView->setItemDelegateForColumn(1, _itemDelegate);

	connect(this, SIGNAL(done()), this, SLOT(accept()));
	connect(this, SIGNAL(cancel()), this, SLOT(reject()));
}

DialogCreateVariable::~DialogCreateVariable() {
	delete _ui;
}

void DialogCreateVariable::setVariable(Variable* variable) {
	_variable = variable;
	_originalName = variable->getName();
	_ui->txtVarName->setText(variable->getName());
	_ui->productionsView->setModel((QAbstractItemModel*)variable->getProductionModel());
	_currentProductionModel = nullptr;
	_currentProductionIndex = QModelIndex();
	_ui->producitionVariableView->setModel(nullptr);
}

Variable* DialogCreateVariable::getVariable() {
	return _variable;
}

void DialogCreateVariable::setMode(DialogCreateVariable::Mode mode) {
	_currentMode = mode;
}

DialogCreateVariable::Mode DialogCreateVariable::getMode() const {
	return _currentMode;
}

void DialogCreateVariable::on_btnAddProduction_clicked() {
	// Create a new production and make it the one being edited

	_ui->productionsView->model()->insertRow(0);

	Production* production = new Production(new VariableSequence(), 1, this);

	_currentProductionIndex = _ui->productionsView->model()->index(0, 0);

	_ui->productionsView->model()->setData(_currentProductionIndex, QVariant::fromValue<void*>((void*)production), Qt::UserRole);

	_ui->producitionVariableView->setModel(((Production*)_ui->productionsView->model()->data(_currentProductionIndex, Qt::UserRole).value<void*>())->getVariableSequenceModel());
	//_ui->txtProductionName->setText(production->getName());
}

void DialogCreateVariable::on_btnRemoveProduction_clicked() {
	ProductionTableModel* model = (ProductionTableModel*)_ui->productionsView->model();
	foreach(QModelIndex index, _ui->productionsView->selectionModel()->selectedIndexes()) {
		model->removeRow(index.row());
	}
}

// Add the currently selected variable to the end of the production
void DialogCreateVariable::on_btnAddToProduction_clicked() {
	if(!_currentProductionModel) return;

	foreach(QModelIndex index, _ui->variableListView->selectionModel()->selectedIndexes()) {
		if(!index.isValid()) continue;
		Variable* var = (Variable*)_ui->variableListView->model()->data(index, Qt::EditRole).value<void*>();

		int row = _currentProductionModel->rowCount(QModelIndex());
		_currentProductionModel->insertRow(row);
		_currentProductionModel->setData(_currentProductionModel->index(row, 0), QVariant::fromValue((void*)var), Qt::UserRole);
	}
}

void DialogCreateVariable::on_btnRemoveFromProduction_clicked() {
	if(!_currentProductionModel) return;
	foreach(QModelIndex index, _ui->producitionVariableView->selectionModel()->selectedIndexes()) {
		_currentProductionModel->removeRow(index.row());
	}
}

// Set up the ability for the production with the specified index to be used.
void DialogCreateVariable::on_productionsView_clicked(const QModelIndex& index) {
	_currentProductionIndex = index;
	Production* production = (Production*)_ui->productionsView->model()->data(index, Qt::UserRole).value<void*>();
	_ui->producitionVariableView->setModel(production->getVariableSequenceModel());
	_currentProductionModel = production->getVariableSequenceModel();
	_ui->txtProductionName->setText(production->getName());
}

void DialogCreateVariable::on_btnBoxOkCancel_accepted() {
	//_ui->lblErorMessage->setText("Accepting!");

	if(_currentMode == CREATE && _lSystem->variableExists(_variable->getName())) {
		_ui->lblErorMessage->setText("Variable name is not unique.");
		return;
	}

	ProductionTableModel* model = (ProductionTableModel*)_ui->productionsView->model();
	for(int i = 0; i < model->rowCount(QModelIndex()); i++) {
		Production* production = (Production*)model->data(model->index(i, 0), Qt::UserRole).value<void*>();

		if(production->getSequence()->length() == 0) {
			_ui->lblErorMessage->setText("Production " + production->getName() + " does not contain any variables.");
			return;
		}
	}

	_ui->lblErorMessage->setText("Accepting!");
	if(_currentMode == CREATE) {
		_lSystem->addVariable(_variable);
	}

	emit done();
}

void DialogCreateVariable::on_btnBoxOkCancel_rejected() {
	delete _variable;
	emit cancel();
}

void DialogCreateVariable::on_txtProductionName_textEdited(const QString& newName) {
	_ui->productionsView->model()->setData(_currentProductionIndex, newName, Qt::DisplayRole);
}

void DialogCreateVariable::on_txtVarName_textEdited(const QString& name) {
	switch(_currentMode) {
	case CREATE:
		_variable->setName(name);
		break;
	case EDIT:
		if(name != _originalName) {
			if(_lSystem->variableExists(name)) {
				_ui->txtVarName->setText(_originalName);
			} else {
				_lSystem->changeVariableName(_originalName, name);
				_originalName = name;
			}
		}
		break;
	}
}
