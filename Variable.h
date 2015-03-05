#ifndef VARIABLE_H
#define VARIABLE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QPair>

#include <random>

class VariableSequence;
class Production;
class ProductionTableModel;

class Variable : public QObject{
	Q_OBJECT
public:
	Variable(QString name =  "Untitled", QObject* parent = nullptr);
	~Variable();

	void addProduction(VariableSequence* const& sequence, int weight, int pos = -1);
	void addProduction(Production* production, int pos = -1);
	void removeProduction(int pos);
	void moveProduction(int oldPos, int newPos);
	Production* getProduction(int pos);
	void setProductionWeight(int pos, int weight);

	Production* getRandomProduction(std::mt19937& generator);

	ProductionTableModel* getProductionModel();

	bool isConstant() const { return _productions->size() == 0; }
	const QString& getName() const { return _name; }
	void setName(QString name) { this->_name = name; }
	int getNumProductions() const;

	void setScript(const QString& script);
	const QString& getScript() const;

private:
	QString _name;
	QString _script;
	QList<Production*>* _productions;
	int _sumOfProductionWeights;
	ProductionTableModel* _productionModel;

	void recalculateProductionWeights();
};

#endif // VARIABLE_H
