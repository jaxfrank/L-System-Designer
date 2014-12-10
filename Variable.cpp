#include "Variable.h"

#include "VariableSequence.h"

Variable::Variable():
	_name(""),
	_sumOfProductionWeights(0),
	_productions()
{}

Variable::Variable(QString name):
	_name(name),
	_sumOfProductionWeights(0),
	_productions()
{}

Production& Variable::getRandomProduction(std::mt19937& generator) {
	std::uniform_int_distribution<> distribution(0, _sumOfProductionWeights - 1);

	int rnd = distribution(generator);
	for(int i = 0; i < _productions.size(); i++) {
		if(rnd < _productions[i].second)
			return _productions[i];

		rnd -= _productions[i].second;
	}
	return *_productions.end();
}

void Variable::addProduction(const VariableSequence& sequence, int weight, int pos) {
	if(pos != -1 && pos >= 0 && pos <= _productions.size()) {
		_productions.insert(_productions.begin() + pos, Production(sequence, weight));
	} else if(pos == -1) {
		_productions.push_back(Production(sequence, weight));
	}
	_sumOfProductionWeights += weight;
}

void Variable::removeProduction(int pos) {
	if(pos < 0 || pos >= _productions.size()) return;
	_sumOfProductionWeights -= _productions[pos].second;
	_productions.erase(_productions.begin() + pos);
}

void Variable::moveProduction(int oldPos, int newPos) {
	if(oldPos < 0 || oldPos >= _productions.size() || newPos < 0 || newPos >= _productions.size() || oldPos == newPos) return;
	Production production = _productions[oldPos];
	_productions.insert(_productions.begin() + newPos, production);
}

Production* Variable::getProduction(int pos) {
	if(pos < 0 || pos >= _productions.size()) return nullptr;
	return &_productions[pos];
}

void Variable::setProductionWeight(int pos, int weight) {
	if(pos < 0 || pos >= _productions.size() || weight <= 0) return;
	_sumOfProductionWeights += weight - _productions[pos].second;
	_productions[pos].second = weight;
}
