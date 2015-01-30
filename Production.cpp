#include "Production.h"

#include "VariableSequenceModel.h"

Production::Production(QObject* parent):
	QObject(parent),
	_name("Untitled"),
	_sequence(new VariableSequence()),
	_weight(1),
	_model(new VariableSequenceModel(_sequence))
{}

Production::Production(VariableSequence* variableSequence, int weight, QObject *parent) :
	QObject(parent),
	_name("Untitled"),
	_sequence(variableSequence),
	_weight(weight),
	_model(nullptr)
{}

Production::~Production() {
	if(_model) delete _model;
	if(_sequence) delete _sequence;
}

VariableSequence* Production::getSequence() {
	if(_sequence == nullptr) {
		_sequence = new VariableSequence();
		_name = "Busted!";
	}
	return _sequence;
}

void Production::setSequence(VariableSequence* sequence) {
	this->_sequence = sequence;
}

int Production::getWeight() {
	return this->_weight;
}

void Production::setWeight(int weight) {
	this->_weight = weight;
}

QString Production::getName() {
	return _name;
}

VariableSequenceModel* Production::getVariableSequenceModel() {
	if(_model == nullptr) _model = new VariableSequenceModel(getSequence());
	return _model;
}

void Production::setName(QString name) {
	_name = name;
}
