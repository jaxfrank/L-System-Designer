#include "Variable.h"

#include "VariableSequence.h"
#include "Production.h"
#include "ProductionTableModel.h"

#include <QObject>

#include <initializer_list>

Variable::Variable(QString name, QObject* parent):
	QObject(parent),
	_name(name),
	_sumOfProductionWeights(0),
	_productions(new QList<Production*>()),
	_productionModel(new ProductionTableModel(_productions)),
	_script("")
{}

Variable::~Variable() {
	delete _productionModel;
	delete _productions;
}

Production* Variable::getRandomProduction(std::mt19937& generator) {
	recalculateProductionWeights();
	if(_sumOfProductionWeights == 1) {
		return *_productions->begin();
	} else {
		std::uniform_int_distribution<int> distribution(0, _sumOfProductionWeights - 1);

		int rnd = distribution(generator);
		for(int i = 0; i < _productions->size(); i++) {
			if(rnd < _productions->at(i)->getWeight())
				return _productions->at(i);

			rnd -= _productions->at(i)->getWeight();
		}
		return *_productions->end();
	}
}

ProductionTableModel* Variable::getProductionModel() {
	return _productionModel;
}

int Variable::getNumProductions() const {
	return _productions->count();
}

void Variable::setScript(const QString& script) {
	_script = script;
}

const QString& Variable::getScript() const {
	return _script;
}

void Variable::recalculateProductionWeights() {
	_sumOfProductionWeights = 0;
	for(int i = 0; i < _productions->size(); i++) {
		_sumOfProductionWeights += _productions->at(i)->getWeight();
	}
}

void Variable::addProduction(VariableSequence* const& sequence, int weight, int pos) {
	if(pos == -1) {
		_productions->push_back(new Production(sequence, weight, this));
	} else if(pos != -1 && pos >= 0 && pos <= _productions->size()) {
		_productions->insert(pos, new Production(sequence, weight, this));
	}
	_sumOfProductionWeights += weight;
}

void Variable::addProduction(Production* production, int pos) {
	if(pos == -1) {
		_productions->push_back(production);
	} else if(pos >= 0 && pos <= _productions->size()) {
		_productions->insert(pos, production);
	} else
	_sumOfProductionWeights += production->getWeight();
}

void Variable::removeProduction(int pos) {
	if(pos < 0 || pos >= _productions->size()) return;
	_sumOfProductionWeights -= _productions->at(pos)->getWeight();
	_productions->erase(_productions->begin() + pos);
}

void Variable::moveProduction(int oldPos, int newPos) {
	if(oldPos < 0 || oldPos >= _productions->size() || newPos < 0 || newPos >= _productions->size() || oldPos == newPos) return;
	Production* production = _productions->at(oldPos);
	_productions->insert(_productions->begin() + newPos, production);
}

Production* Variable::getProduction(int pos) {
	if(pos < 0 || pos >= _productions->size()) return nullptr;
	return (*_productions)[pos];
}

void Variable::setProductionWeight(int pos, int weight) {
	if(pos < 0 || pos >= _productions->size() || weight <= 0) return;
	_sumOfProductionWeights += weight - (*_productions)[pos]->getWeight();
	(*_productions)[pos]->setWeight(weight);
}
