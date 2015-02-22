#include "DialogCreateAxiom.h"
#include "ui_DialogCreateAxiom.h"

#include "Variable.h"
#include "VariableSequence.h"
#include "VariableSequenceModel.h"
#include "LSystem.h"

#include <QString>
#include <QModelIndex>
#include <QModelIndexList>

DialogCreateAxiom::DialogCreateAxiom(LSystem* lSystem, QWidget *parent) :
	QDialog(parent),
	_ui(new Ui::DialogCreateAxiom),
	_lSystem(lSystem),
	_variableSequenceModel(lSystem->getVariableModel()),
	_axiomVariableSequenceModel(nullptr),
	_mode(CREATE),
	_originalName("")
{
	_ui->setupUi(this);
	_ui->variableView->setModel(lSystem->getVariableModel());

	connect(this, SIGNAL(done()), this, SLOT(accept()));
	connect(this, SIGNAL(cancel()), this, SLOT(reject()));
}

DialogCreateAxiom::~DialogCreateAxiom() {
	delete _ui;
}

void DialogCreateAxiom::setAxiom(VariableSequenceModel* sequence) {
	_axiomVariableSequenceModel = sequence;
	QString name = sequence->data(QModelIndex(), Qt::DisplayRole).value<QString>();
	_ui->txtBoxName->setText(name);
	_originalName = name;

	_ui->axiomView->setModel(sequence);
}

VariableSequence* DialogCreateAxiom::getAxiom() {
	return nullptr;
}

void DialogCreateAxiom::setMode(DialogCreateAxiom::Mode mode) {
	_mode = mode;
}

DialogCreateAxiom::Mode DialogCreateAxiom::getMode() {
	return _mode;
}

void DialogCreateAxiom::on_btnAdd_clicked() {
	QModelIndexList indexList = _ui->variableView->selectionModel()->selectedIndexes();
	int row = _axiomVariableSequenceModel->rowCount(QModelIndex());
	_axiomVariableSequenceModel->insertRows(row, indexList.length(), QModelIndex());
	for(int i = 0; i < indexList.length(); i++) {
		_axiomVariableSequenceModel->setData(_axiomVariableSequenceModel->index(row + i), _variableSequenceModel->data(indexList[i], Qt::EditRole), Qt::EditRole);
	}
}

void DialogCreateAxiom::on_btnRemove_clicked() {
	QModelIndexList indexList = _ui->axiomView->selectionModel()->selectedIndexes();
	if(indexList.length() > 0) {
		_axiomVariableSequenceModel->removeRow(indexList.at(0).row());
	}
}

void DialogCreateAxiom::on_btnMoveDown_clicked() {

}

void DialogCreateAxiom::on_btnMoveUp_clicked() {

}

void DialogCreateAxiom::on_txtBoxName_textEdited(const QString& name) {
	_axiomVariableSequenceModel->setData(QModelIndex(), name, Qt::DisplayRole);
}

void DialogCreateAxiom::on_buttonBox_accepted() {
	QString name;
	switch(_mode) {
	case EDIT:
		name = _axiomVariableSequenceModel->data(QModelIndex(), Qt::DisplayRole).value<QString>();
		if(name != _originalName && _lSystem->axiomExists(name)) {
			_ui->lblErrorMessage->setText("Axiom name is not Unique!");
			return;
		} else if(_axiomVariableSequenceModel->rowCount(QModelIndex()) == 0) {
			_ui->lblErrorMessage->setText("Must contain at least one variable!");
			return;
		}
		if(name != _originalName) {
			_lSystem->changeAxiomName(_originalName, name);
		}
		emit done();
		return;
		break;
	case CREATE:
		name = _axiomVariableSequenceModel->data(QModelIndex(), Qt::DisplayRole).value<QString>();
		if(_lSystem->axiomExists(name)) {
			_ui->lblErrorMessage->setText("Axiom name is not Unique!");
			return;
		} else if(_axiomVariableSequenceModel->rowCount(QModelIndex()) == 0) {
			_ui->lblErrorMessage->setText("Must contain at least one variable!");
			return;
		}
		VariableSequence* sequence = (VariableSequence*)_axiomVariableSequenceModel->data(QModelIndex(), Qt::UserRole).value<void*>();

		_lSystem->addAxiom(sequence);
		emit done();
		return;
		break;
	}
}
