#ifndef VARIABLE_SEQUENCE_LIST_MODEL_H
#define VARIABLE_SEQUENCE_LIST_MODEL_H

#include <QAbstractListModel>
#include <QList>

class VariableSequence;

class VariableSequenceListModel : public QAbstractListModel {
	Q_OBJECT
public:
	explicit VariableSequenceListModel(QList<VariableSequence*>* variableSequences, QObject *parent = 0);

	int rowCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role);

	bool insertRows(int row, int count, const QModelIndex& parent);
	bool removeRows(int row, int count, const QModelIndex& parent);

private:
	QList<VariableSequence*>* _variableSequences;

};

#endif // VARIABLE_SEQUENCE_LIST_MODEL_H
