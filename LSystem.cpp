#include "LSystem.h"

#include "VariableSequence.h"
#include "Variable.h"
#include "VariableSequenceModel.h"

LSystem::LSystem(QObject* parent):
	QObject(parent),
	_variableModel(new VariableSequenceModel(new VariableSequence("Variables", this), this)),
	_variableLookup(new QHash<QString, Variable*>())
{}

LSystem::~LSystem() {
	foreach(VariableSequence* sequence, _axioms) {
		delete sequence;
	}
	delete _variableModel;
	foreach(Variable* variable, *_variableLookup) {
		delete variable;
	}
}

int LSystem::getNumVariables() const {
	return _variableModel->rowCount(QModelIndex());
}

int LSystem::getNumAxioms() const {
	return _axioms.size();
}

void LSystem::addVariable(Variable* variable) {
	_variableLookup->insert(variable->getName(), variable);

	_variableModel->insertRow(0, QModelIndex());
	_variableModel->setData(_variableModel->index(0, 0), QVariant::fromValue((void*)variable), Qt::DisplayRole);
}

Variable* LSystem::getVariable(QString& name) {
	auto iter = _variableLookup->find(name);
	if(iter != _variableLookup->end()) {
		return *iter;
	} else {
		return nullptr;
	}
}

Variable* LSystem::getVariable(int index) {
	if(index < 0 || index >= _variableModel->rowCount(QModelIndex())) return nullptr;
	return (Variable*)_variableModel->data(_variableModel->index(index), Qt::UserRole).value<void*>();
}

bool LSystem::variableExists(const QString& name) const {
	return _variableLookup->contains(name);
}

void LSystem::changeVariableName(const QString& originalName, const QString& newName) {
	auto iter = _variableLookup->find(originalName);
	if(iter != _variableLookup->end()) {
		Variable* var = *iter;
		_variableLookup->remove(originalName);
		var->setName(newName);
		_variableLookup->insert(newName, var);
	}
}

VariableSequenceModel*LSystem::getVariableModel() {
	return _variableModel;
}

VariableSequence* LSystem::getAxiom(int index) {
	if(index < 0 || index >= _axioms.size()) return nullptr;
	return _axioms[index];
}

QList<VariableSequence*>* LSystem::getAxioms() {
	return &_axioms;
}
