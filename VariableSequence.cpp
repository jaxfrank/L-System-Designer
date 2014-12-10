#include "VariableSequence.h"

#include "Variable.h"

VariableSequence::VariableSequence():
	_variables()
{}

const Variable* const VariableSequence::at(int i) const {
	if(i < 0 || i >= _variables.size()) return nullptr;

	return _variables.at(i);
}

bool VariableSequence::operator==(const VariableSequence& rhs) {
	if(this->length() != rhs.length()) return false;
	for(int i = 0; i < rhs.length(); i++) {
		if(this->at(i) != rhs.at(i)) return false;
	}
	return true;
}

bool VariableSequence::operator!=(const VariableSequence& rhs) {
	return !(*this == rhs);
}

Variable*& VariableSequence::operator[](size_t pos) {
	return _variables[pos];
}

const Variable* const VariableSequence::operator[](size_t pos) const {
	return _variables[pos];
}

void VariableSequence::push_back(Variable* variable) {
	_variables.push_back(variable);
}

void VariableSequence::push_back(const VariableSequence& sequence) {
	_variables.insert(_variables.end(), sequence._variables.begin(), sequence._variables.end());
}

void VariableSequence::pop_back() {
	_variables.pop_back();
}

void VariableSequence::insert(int pos, Variable* variable) {
	if(pos < 0 || pos > _variables.size()) return;

	_variables.insert(_variables.begin() + pos, variable);
}

void VariableSequence::clear() {
	_variables.clear();
}

const Variable* const VariableSequence::front() const {
	return _variables.front();
}

const Variable* VariableSequence::front() {
	return _variables.front();
}

const Variable* const VariableSequence::back() const {
	return _variables.back();
}

const Variable*VariableSequence::back() {
	return _variables.back();
}
