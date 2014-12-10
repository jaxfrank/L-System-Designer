#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <utility>
#include <unordered_map>
#include <unordered_set>

class Variable;
class VariableSequence;

class LSystem {
public:
	LSystem();
	~LSystem();

private:
	std::unordered_set<Variable*> _variables;
	std::vector<VariableSequence*> _axioms;
};

#endif // LSYSTEM_H
