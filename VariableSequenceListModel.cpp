#include "VariableSequenceListModel.h"

#include "VariableSequence.h"

VariableSequenceListModel::VariableSequenceListModel(QList<VariableSequence*>* sequences, QObject *parent) :
	QAbstractListModel(parent),
	_variableSequenes(sequences)
{}

int VariableSequenceListModel::rowCount(const QModelIndex& parent) const {
	return _variableSequenes->length();
}

QVariant VariableSequenceListModel::data(const QModelIndex& index, int role) const {
	if(!index.isValid() || index.row() < 0 || index.row() >= _variableSequenes->length()) return QVariant();
	switch(role) {
	case Qt::DisplayRole:
		return _variableSequenes->at(index.row())->getName();
	case Qt::EditRole:
	case Qt::UserRole:
		return QVariant::fromValue<void*>((void*)_variableSequenes->at(index.row()));
	default:
		QVariant();
	}
}
