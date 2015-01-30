#include "VariableSequenceModel.h"

#include "Variable.h"

#include <QDebug>

VariableSequenceModel::VariableSequenceModel(VariableSequence* sequence, QObject *parent):
	QAbstractListModel(parent),
	_sequence(sequence)
{}


int VariableSequenceModel::rowCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);
	if(_sequence == nullptr) {
		return 0;
	} else {
		return (int)_sequence->length();
	}
}

QVariant VariableSequenceModel::data(const QModelIndex& index, int role) const {
	if(!index.isValid()) return QVariant();
	switch(role) {
	case Qt::DisplayRole:
		return _sequence->at(index.row())->getName();
	case Qt::UserRole:
	case Qt::EditRole:
		return QVariant::fromValue((void*)_sequence->at(index.row()));
	default:
		return QVariant();
	}
}

bool VariableSequenceModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if(index.row() < 0 || index.row() >= _sequence->length()) return false;
	Variable* var = (Variable*)value.value<void*>();
	_sequence->set(index.row(), var);

	QVector<int> roles;
	roles << role;
	emit dataChanged(index, index, roles);
	return true;
}

bool VariableSequenceModel::insertRows(int row, int count, const QModelIndex& parent) {
	if(count <= 0) return true;
	beginInsertRows(parent, row, row + count - 1);
	while(count--) _sequence->insert(row, NULL);
	endInsertRows();
	return true;
}

bool VariableSequenceModel::removeRows(int row, int count, const QModelIndex& parent) {
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	while(count--) _sequence->remove(row);
	endRemoveRows();
	return true;
}


bool VariableSequenceModel::moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent, int destinationChild) {
	beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent, destinationChild);
	VariableSequence removed;
	for(int i = 0; i < count; i++) {
		removed.pushBack(_sequence->at(sourceRow));
		_sequence->remove(sourceRow);
	}
	for(int i = 0; i < removed.length(); i++) {
		_sequence->insert(destinationChild - count + i, removed.at(0));
		removed.popFront();
	}
	endMoveRows();
	return true;
}
