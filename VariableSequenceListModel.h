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

private:
	QList<VariableSequence*>* _variableSequenes;
};

#endif // VARIABLE_SEQUENCE_LIST_MODEL_H
