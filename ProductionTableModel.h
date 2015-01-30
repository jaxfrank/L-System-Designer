#ifndef PRODUCTIONTABLEMODEL_H
#define PRODUCTIONTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>

#include "Production.h"

class ProductionTableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	explicit ProductionTableModel(QList<Production*>* production, QObject *parent = 0);

	int rowCount(const QModelIndex& parent) const;
	bool insertRows(int row, int count, const QModelIndex& parent);
	bool removeRows(int row, int count, const QModelIndex& parent);

	int columnCount(const QModelIndex& parent) const;

	QVariant data(const QModelIndex& index, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role);

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	Qt::ItemFlags flags(const QModelIndex& index) const;

private:
	QList<Production*>* _productions;

};

#endif // PRODUCTIONTABLEMODEL_H
