#include "Simulator.h"

#include "Variable.h"
#include "VariableSequence.h"
#include "LSystem.h"
#include "Production.h"

#include <QDateTime>

#include <random>

#include <cstdlib>
#include <ctime>

Simulator::Simulator():
	_lSystem(nullptr),
	_seed(0)
{
	std::srand(std::time(0));
}

VariableSequence* Simulator::simulate(int recurseLevel) {
	if(recurseLevel <= 0) return nullptr;
	if(!_lSystem) return nullptr;
	if(_lSystem->getNumVariables() <= 0) return nullptr;
	if(_lSystem->getNumAxioms() <= 0) return nullptr;

	VariableSequence* axiom = _lSystem->getAxiom(0);

	std::mt19937 rng(_seed);

	VariableSequence* current = new VariableSequence();
	VariableSequence* previous = axiom;

	while(recurseLevel--) {
		for(int i = 0; i < previous->length(); i++) {
			if(!previous->at(i)->isConstant()) {
				current->pushBack(previous->at(i)->getRandomProduction(rng)->getSequence());
			} else {
				current->pushBack(previous->at(i));
			}
		}
		if(previous != axiom) delete previous;
		previous = current;
		current = new VariableSequence();
	}
	VariableSequence* result = new VariableSequence();
	result->pushBack(previous);
	delete current;
	delete previous;
	return result;
}

LSystem*Simulator::getLSystem() {
	return _lSystem;
}

void Simulator::setLSystem(LSystem* lSystem) {
	_lSystem = lSystem;
}

unsigned long Simulator::getSeed() const {
	return _seed;
}

void Simulator::setSeed(unsigned long seed) {
	_seed = seed;
}

unsigned long Simulator::generateSeed() {
	setSeed(std::rand());
	return getSeed();
}
