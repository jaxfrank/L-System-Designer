#include "VariableSequenceRenderer.h"

#include <QtGui>
#include <QGraphicsLineItem>
#include <QtMath>

#include "Variable.h"
#include "VariableSequence.h"

#include <cstdlib>

VariableSequenceRenderer::VariableSequenceRenderer():
	_graphicsScene(new QGraphicsScene()),
	_scriptEngine(new QScriptEngine()),
	_angleStack(),
	_positionStack(),
	_colorStack(),
	_angle(0),
	_position(QPointF(0,0)),
	_pen(QPen(Qt::black))
{
	_pen.setWidth(3);

	QScriptValue obj = _scriptEngine->newQObject(this);
	_scriptEngine->globalObject().setProperty("renderer", obj);
}

void VariableSequenceRenderer::evaluateSequence() {
	if(!_sequence) return;
	if(_sequence->length() == 0) return;
	clearScene();

	for(int i = 0; i < _sequence->length(); i++) {
		Variable* var = _sequence->at(i);
		 _scriptEngine->evaluate(var->getScript());
	}
}

VariableSequence*VariableSequenceRenderer::getSequence() {
	return _sequence;
}

void VariableSequenceRenderer::setSequence(VariableSequence* sequence) {
	 _sequence = sequence;
}

QGraphicsScene* VariableSequenceRenderer::getScene() {
	return _graphicsScene;
}

QScriptEngine*VariableSequenceRenderer::getScriptEngine() {
	return _scriptEngine;
}

void VariableSequenceRenderer::pushPos() {
	_positionStack.push(_position);
}

void VariableSequenceRenderer::popPos() {
	_position = _positionStack.pop();
}

void VariableSequenceRenderer::pushAngle() {
	_angleStack.push(_angle);
}

void VariableSequenceRenderer::popAngle() {
	_angle = _angleStack.pop();
}

void VariableSequenceRenderer::pushColor() {
	_colorStack.push(_pen.color());
}

void VariableSequenceRenderer::popColor() {
	_pen.setColor(_colorStack.pop());
}

void VariableSequenceRenderer::turn(float angle) {
	_angle += qDegreesToRadians(angle);
}

void VariableSequenceRenderer::move(float xDist, float yDist) {
	_position += QPointF(xDist, yDist);
}

void VariableSequenceRenderer::moveForward(float dist) {
	_position += QPointF(dist * qCos(_angle), dist * qSin(_angle));
}

void VariableSequenceRenderer::drawLine(float length) {
	QLineF line(_position, QPointF(length * qCos(_angle), length * qSin(_angle)) + _position);
	_graphicsScene->addLine(line, _pen);
}

void VariableSequenceRenderer::setColor(int r, int g, int b) {
	_pen.setColor(QColor(r, g, b));
}

void VariableSequenceRenderer::setLineWidth(int lineWidth) {
	_pen.setWidth(lineWidth);
}

double VariableSequenceRenderer::rand() {
	return std::rand();
}

void VariableSequenceRenderer::clearScene() {
	QList<QGraphicsItem*> items = _graphicsScene->items();
	while(!items.isEmpty()) {
		delete items.first();
		items.removeFirst();
	}
	_position = QPointF(0,0);
	_pen.setWidth(3);
	_pen.setColor(Qt::black);
	_angle = 0;
	_angleStack.clear();
	_positionStack.clear();
	_colorStack.clear();
}
