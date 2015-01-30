#include "VariableSequence.h"

#include "Variable.h"

VariableSequence::VariableSequence(QString name, QObject* parent):
	QObject(parent),
	_name(name),
	_variables()
{}

Variable* VariableSequence::at(int i) {
	if(i < 0 || i >= _variables.size()) return nullptr;

	return _variables.at(i);
}

bool VariableSequence::operator==(const VariableSequence& rhs) {
	if(this->length() != rhs.length()) return false;
	for(int i = 0; i < rhs.length(); i++) {
		if(_variables[i] != rhs._variables[i]) return false;
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

bool VariableSequence::contains(Variable* variable) const {
	return _variables.contains(variable);
}

void VariableSequence::pushFront(Variable* variable) {
	_variables.push_front(variable);
}

void VariableSequence::pushFront(const VariableSequence& sequence) {
	for(int i = sequence.length() - 1; i >= 0; i--) {
		_variables.push_front(sequence._variables.at(i));
	}
}

void VariableSequence::popFront() {
	if(length() == 0) return;

	_variables.pop_front();
}

void VariableSequence::pushBack(Variable* variable) {
	_variables.push_back(variable);
}

void VariableSequence::pushBack(const VariableSequence& sequence) {
	_variables << sequence._variables;
}

void VariableSequence::popBack() {
	if(length() == 0) return;

	_variables.pop_back();
}

void VariableSequence::insert(int pos, Variable* variable) {
	if(pos < 0 || pos > _variables.size()) return;

	_variables.insert(_variables.begin() + pos, variable);
}

void VariableSequence::set(int pos, Variable* variable) {
	if(pos < 0 || pos >= _variables.size()) return;

	_variables[pos] = variable;
}

void VariableSequence::remove(int pos) {
	if(pos < 0 || pos > _variables.size()) return;
	_variables.removeAt(pos);
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

void VariableSequence::setName(QString name) {
	_name = name;
}

QString VariableSequence::getName() {
	return _name;
}
