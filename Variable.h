#ifndef VARIABLE_H
#define VARIABLE_H

#include <QString>

#include <vector>
#include <utility>
#include <random>

class VariableSequence;

typedef std::pair<VariableSequence, int> Production;

class Variable {
public:
	Variable(QString name);
	Variable();

	void addProduction(const VariableSequence& sequence, int weight, int pos = -1);
	void removeProduction(int pos);
	void moveProduction(int oldPos, int newPos);
	Production* getProduction(int pos);
	void setProductionWeight(int pos, int weight);

	Production& getRandomProduction(std::mt19937& generator);

	bool isConstant() const { return _productions.size() == 0; }
	const QString& getName() const { return _name; }

private:
	QString _name;
	std::vector<Production> _productions;
	int _sumOfProductionWeights;
};

#endif // VARIABLE_H
