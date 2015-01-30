#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <QObject>
#include <QString>

class VariableSequence;
class VariableSequenceModel;

class Production : public QObject {
	Q_OBJECT
public:
	explicit Production(QObject* parent = nullptr);
	explicit Production(VariableSequence* sequence, int weight, QObject *parent = nullptr);
	~Production();

	void setSequence(VariableSequence* sequence);
	VariableSequence* getSequence();
	void setWeight(int weight);
	int getWeight();

	void setName(QString name);
	QString getName();

	VariableSequenceModel* getVariableSequenceModel();

private:
	QString _name;
	VariableSequence* _sequence;
	VariableSequenceModel* _model;
	int _weight;

signals:

public slots:

};

#endif // PRODUCTION_H
