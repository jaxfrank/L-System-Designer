#ifndef SIMULATOR_H
#define SIMULATOR_H

class VariableSequence;
class LSystem;

class Simulator {
public:
	Simulator();

	VariableSequence* simulate(int recurseLevel);

	LSystem* getLSystem();
	void setLSystem(LSystem* lSystem);

	unsigned long getSeed() const;
	void setSeed(unsigned long seed);
	unsigned long generateSeed();

private:
	LSystem* _lSystem;
	unsigned long _seed;
};

#endif // SIMULATOR_H
