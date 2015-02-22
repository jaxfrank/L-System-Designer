#include "LSystem.h"

#include "VariableSequence.h"
#include "Variable.h"
#include "VariableSequenceModel.h"
#include "VariableSequenceListModel.h"

#include <QDebug>

LSystem::LSystem(QObject* parent):
	QObject(parent),
	_variableModel(new VariableSequenceModel(new VariableSequence("Variables", this), this)),
	_variableLookup(new QHash<QString, Variable*>()),
	_axioms(new VariableSequenceListModel(new QList<VariableSequence*>(), this)),
	_axiomNames()
{}

LSystem::~LSystem() {
	for(int i = 0; i < _axioms->rowCount(QModelIndex()); i++) {
		delete (VariableSequence*)_axioms->data(_axioms->index(i), Qt::EditRole).value<void*>();
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
	return _axioms->rowCount(QModelIndex());
}

void LSystem::addVariable(Variable* variable) {
	_variableLookup->insert(variable->getName(), variable);

	_variableModel->insertRow(0, QModelIndex());
	_variableModel->setData(_variableModel->index(0, 0), QVariant::fromValue<void*>((void*)variable), Qt::EditRole);
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
	if(index < 0 || index >= _axioms->rowCount(QModelIndex())) return nullptr;
	return (VariableSequence*)_axioms->data(_axioms->index(index, 0), Qt::EditRole).value<void*>();
}

void LSystem::addAxiom(VariableSequence* axiom) {
	_axiomNames.insert(axiom->getName());

	_axioms->insertRows(0, 1, QModelIndex());
	_axioms->setData(_axioms->index(0, 0), QVariant::fromValue<void*>((void*)axiom), Qt::EditRole);
}

bool LSystem::axiomExists(const QString& name) const {
	return _axiomNames.contains(name);
}

void LSystem::changeAxiomName(const QString& originalName, const QString& newName) {
	auto iter = _axiomNames.find(originalName);
	if(iter != _axiomNames.end()) {
		_axiomNames.remove(originalName);
		_axiomNames.insert(newName);
	}
}

VariableSequenceListModel* LSystem::getAxiomModel() {
	return _axioms;
}
