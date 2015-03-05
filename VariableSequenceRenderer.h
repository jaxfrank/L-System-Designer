#ifndef VARIABLE_SEQUENCE_RENDERER_H
#define VARIABLE_SEQUENCE_RENDERER_H

#include <QGraphicsScene>
#include <QScriptEngine>
#include <QDebug>
#include <QStack>

class VariableSequence;

class VariableSequenceRenderer : public QObject {
	Q_OBJECT
public:
	VariableSequenceRenderer();

	void evaluateSequence();

	VariableSequence* getSequence();
	void setSequence(VariableSequence* sequence);

	QGraphicsScene* getScene();
	QScriptEngine* getScriptEngine();

	Q_INVOKABLE void pushPos();
	Q_INVOKABLE void popPos();
	Q_INVOKABLE void pushAngle();
	Q_INVOKABLE void popAngle();
	Q_INVOKABLE void pushColor();
	Q_INVOKABLE void popColor();
	Q_INVOKABLE void turn(float angle);
	Q_INVOKABLE void move(float xDist, float yDist);
	Q_INVOKABLE void moveForward(float dist);
	Q_INVOKABLE void drawLine(float length);
	Q_INVOKABLE void setColor(int r, int g, int b);
	Q_INVOKABLE void setLineWidth(int lineWidth);
	Q_INVOKABLE double rand();

private:
	QGraphicsScene* _graphicsScene;
	QScriptEngine* _scriptEngine;
	VariableSequence* _sequence;

	QStack<float> _angleStack;
	QStack<QPointF> _positionStack;
	QStack<QColor> _colorStack;

	float _angle;
	QPointF _position;
	QPen _pen;

	void clearScene();
};

#endif // VARIABLE_SEQUENCE_RENDERER_H
