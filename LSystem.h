#ifndef L_SYSTEM_H
#define L_SYSTEM_H

#include <QObject>
#include <QAbstractItemModel>
#include <QList>
#include <QHash>
#include <QSet>

class Variable;
class VariableSequence;
class VariableSequenceModel;
class VariableSequenceListModel;

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

	VariableSequenceListModel* getAxiomModel();
	VariableSequence* getAxiom(int index);
	void addAxiom(VariableSequence* axiom);

	bool axiomExists(const QString& name) const;
	void changeAxiomName(const QString& originalName, const QString& newName);

private:
	VariableSequenceModel* _variableModel;
	QHash<QString, Variable*>* _variableLookup;

	VariableSequenceListModel* _axioms;
	QSet<QString> _axiomNames;
};

#endif // L_SYSTEM_H
