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
	if(!index.isValid()) {
		if(role == Qt::DisplayRole) {
			return _sequence->getName();
		} else if(role == Qt::UserRole){
			return QVariant::fromValue<void*>((void*)_sequence);
		} else {
			return QVariant();
		}
	}

	switch(role) {
	case Qt::DisplayRole:
		return _sequence->at(index.row())->getName();
	case Qt::EditRole:
		return QVariant::fromValue<void*>((void*)_sequence->at(index.row()));
	case Qt::UserRole:
		return QVariant::fromValue<void*>((void*)_sequence);
	default:
		return QVariant();
	}
}

bool VariableSequenceModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	Variable* var;
	switch(role) {
	case Qt::EditRole:
	case Qt::UserRole:
		if(index.row() < 0 || index.row() >= _sequence->length()) return false;
		var = (Variable*)value.value<void*>();
		_sequence->set(index.row(), var);
		break;
	case Qt::DisplayRole:
		_sequence->setName(value.value<QString>());
		break;
	}
	QVector<int> roles;
	roles << role;
	emit dataChanged(index, index, roles);
	return true;
}

bool VariableSequenceModel::insertRows(int row, int count, const QModelIndex& parent) {
	if(count <= 0) return true;
	beginInsertRows(parent, row, row + count - 1);
	while(count--) _sequence->insert(row, nullptr);
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
