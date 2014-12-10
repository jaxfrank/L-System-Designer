#ifndef VARIABLE_SEQUENCE_H
#define VARIABLE_SEQUENCE_H

#include <vector>

class Variable;

class VariableSequence {
public:
	VariableSequence();

	bool operator==(const VariableSequence& rhs);
	bool operator!=(const VariableSequence& rhs);

	const Variable* const at(int i) const;

	Variable*& operator[](size_t pos);
	const Variable* const operator[](size_t pos) const;

	void push_back(Variable* variable);
	void push_back(const VariableSequence& sequence);
	void pop_back();
	void insert(int pos, Variable* variable);
	void clear();

	const Variable* const front() const;
	const Variable* front();
	const Variable* const back() const;
	const Variable* back();

	size_t length() const { return _variables.size(); }
private:
	std::vector<Variable*> _variables;
};

#endif // VARIABLE_SEQUENCE_H
