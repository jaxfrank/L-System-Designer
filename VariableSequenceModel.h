#ifndef VARIABLE_SEQUENCE_MODEL
#define VARIABLE_SEQUENCE_MODEL

#include <QAbstractListModel>

#include "VariableSequence.h"

class VariableSequenceModel : public QAbstractListModel {
	Q_OBJECT
public:
	explicit VariableSequenceModel(VariableSequence* sequence, QObject *parent = 0);

	QVariant data(const QModelIndex& index, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role);

	int rowCount(const QModelIndex& parent) const;

	bool insertRows(int row, int count, const QModelIndex& parent);
	bool removeRows(int row, int count, const QModelIndex& parent);
	bool moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent, int destinationChild);

private:
	VariableSequence* _sequence;

signals:

public slots:

};

#endif // VARIABLE_SEQUENCE_MODEL
