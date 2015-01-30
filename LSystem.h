#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <QObject>
#include <QAbstractItemModel>
#include <QList>
#include <QHash>

class Variable;
class VariableSequence;
class VariableSequenceModel;

class LSystem : public QObject {
	Q_OBJECT
public:
	LSystem(QObject* parent = 0);
	~LSystem();

	int getNumVariables() const;
	int getNumAxioms() const;

	void addVariable(Variable* variable);
	Variable* getVariable(QString& name);
	Variable* getVariable(int index);
	bool variableExists(const QString& name) const;
	void changeVariableName(const QString& originalName, const QString& newName);

	VariableSequenceModel* getVariableModel();

	VariableSequence* getAxiom(int index);
	QList<VariableSequence*>* getAxioms();

private:
	VariableSequenceModel* _variableModel;
	QList<VariableSequence*> _axioms;

	QHash<QString, Variable*>* _variableLookup;
};

#endif // L_SYSTEM_H
