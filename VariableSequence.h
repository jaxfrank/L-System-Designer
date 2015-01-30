#ifndef VARIABLE_SEQUENCE_H
#define VARIABLE_SEQUENCE_H

#include <QObject>
#include <QList>
#include <QString>

class Variable;

class VariableSequence : public QObject {
	Q_OBJECT
public:
	VariableSequence(QString name = "Untitled", QObject* parent = nullptr);

	bool operator==(const VariableSequence& rhs);
	bool operator!=(const VariableSequence& rhs);

	Variable* at(int i);

	Variable*& operator[](size_t pos);
	const Variable* const operator[](size_t pos) const;

	bool contains(Variable* variable) const;

	void pushFront(Variable* variable);
	void pushFront(const VariableSequence& sequence);
	void popFront();

	void pushBack(Variable* variable);
	void pushBack(const VariableSequence& sequence);
	void popBack();

	void insert(int pos, Variable* variable);
	void set(int pos, Variable* variable);

	void remove(int pos);
	void clear();

	const Variable* const front() const;
	const Variable* front();
	const Variable* const back() const;
	const Variable* back();

	size_t length() const { return _variables.count(); }

	void setName(QString name);
	QString getName();

private:
	QString _name;
	QList<Variable*> _variables;
};

#endif // VARIABLE_SEQUENCE_H
