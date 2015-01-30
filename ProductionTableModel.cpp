#include "ProductionTableModel.h"

#include <QString>

ProductionTableModel::ProductionTableModel(QList<Production*>* productions, QObject *parent) :
	QAbstractTableModel(parent),
	_productions(productions)
{}

int ProductionTableModel::rowCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);
	return _productions->size();
}

bool ProductionTableModel::insertRows(int row, int count, const QModelIndex& parent) {
	if(row > _productions->size()) return false;

	beginInsertRows(parent, row, row + count - 1);
	while(count--) _productions->insert(row, nullptr);
	endInsertRows();

	return true;
}

bool ProductionTableModel::removeRows(int row, int count, const QModelIndex& parent) {
	if(row >= _productions->size() || row < 0) return false;
	beginRemoveRows(parent, row, row + count -1);
	while(count--) {
		Production* p = _productions->at(row);
		_productions->removeAt(row);
		delete p;
	}
	endRemoveRows();
	return true;
}

int ProductionTableModel::columnCount(const QModelIndex& parent) const {
	Q_UNUSED(parent);
	return 2;
}

QVariant ProductionTableModel::data(const QModelIndex& index, int role) const {
	if(!index.isValid()) return QVariant();
	if(index.row() < 0 || index.row() >= _productions->size()) return QVariant();
	if(_productions->at(index.row()) == nullptr) return QVariant();

	switch(role) {
	case Qt::DisplayRole:
		if(index.column() == 0) {
			return _productions->at(index.row())->getName();
		} else if(index.column() == 1) {
			return QVariant::fromValue<int>(_productions->at(index.row())->getWeight());
		} else {
			return QVariant();
		}
		break;
	case Qt::UserRole:
		return QVariant::fromValue<void*>((void*)_productions->at(index.row()));
		break;
	case Qt::EditRole:
		if(index.column() == 0) {
			return _productions->at(index.row())->getName();
		} else if(index.column() == 1) {
			return QVariant::fromValue<int>(_productions->at(index.row())->getWeight());
		}
		break;
	default:
		return QVariant();
	}
	return QVariant();
}

bool ProductionTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if(!index.isValid()) return false;
	if(index.row() < 0 || index.row() >= _productions->size()) return false;

	Production* production = (Production*)value.value<void*>();
	switch(role) {
	case Qt::UserRole:
		(*_productions)[index.row()] = production;
		//_productions->replace(index.row(), prodution);
		break;
	case Qt::DisplayRole:
		_productions->at(index.row())->setName(value.value<QString>());
		break;
	case Qt::EditRole:
		if(index.column() == 0) {
			_productions->at(index.row())->setName(value.value<QString>());
		} else if(index.column() == 1) {
			_productions->at(index.row())->setWeight(value.value<int>());
		}
		break;
	}
	QVector<int> roles;
	roles << role;
	emit dataChanged(index, index, roles);
	return true;
}


QVariant ProductionTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if(role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		if(section == 0) return QString("Name");
		else if(section == 1) return QString("Weight");
		else return QVariant();
	} else {
		return QVariant();
	}
}


Qt::ItemFlags ProductionTableModel::flags(const QModelIndex& index) const {
	if(index.column() == 1) {
		return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	} else {
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
}
