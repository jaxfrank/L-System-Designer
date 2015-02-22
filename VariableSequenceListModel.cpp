#include "VariableSequenceListModel.h"

#include "VariableSequence.h"

VariableSequenceListModel::VariableSequenceListModel(QList<VariableSequence*>* sequences, QObject *parent) :
	QAbstractListModel(parent),
	_variableSequences(sequences)
{}

int VariableSequenceListModel::rowCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);

	return _variableSequences->length();
}

QVariant VariableSequenceListModel::data(const QModelIndex& index, int role) const {
	if(!index.isValid() || index.row() < 0 || index.row() >= _variableSequences->length()) return QVariant();
	switch(role) {
	case Qt::DisplayRole:
		return _variableSequences->at(index.row())->getName();
	case Qt::EditRole:
		return QVariant::fromValue<void*>((void*)_variableSequences->at(index.row()));
	case Qt::UserRole:
		return QVariant::fromValue<void*>((void*)_variableSequences->at(index.row())->getModel());
	default:
		return QVariant();
	}
}

bool VariableSequenceListModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	VariableSequence* sequence;
	switch(role) {
	case Qt::EditRole:
	case Qt::UserRole:
		if(index.row() < 0 || index.row() >= _variableSequences->length()) return false;
		sequence = (VariableSequence*)value.value<void*>();
		(*_variableSequences)[index.row()] = sequence;
		break;
	}

	QVector<int> roles;
	roles << role;
	emit dataChanged(index, index, roles);
	return true;
}


bool VariableSequenceListModel::insertRows(int row, int count, const QModelIndex& parent) {
	if(count <= 0) return true;
	beginInsertRows(parent, row, row + count - 1);
	while(count--) _variableSequences->insert(row, nullptr);
	endInsertRows();
	return true;
}


bool VariableSequenceListModel::removeRows(int row, int count, const QModelIndex& parent) {
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	while(count--) {
		delete _variableSequences->at(row);
		_variableSequences->removeAt(row);
	}
	endRemoveRows();
	return true;
}
