#include "DialogCreateAxiom.h"
#include "ui_DialogCreateAxiom.h"

DialogCreateAxiom::DialogCreateAxiom(QWidget *parent) :
	QDialog(parent),
	_ui(new Ui::DialogCreateAxiom)
{
	_ui->setupUi(this);
}

DialogCreateAxiom::~DialogCreateAxiom() {
	delete _ui;
}

void DialogCreateAxiom::on_btnAdd_clicked() {

}

void DialogCreateAxiom::on_btnRemove_clicked() {

}

void DialogCreateAxiom::on_btnMoveDown_clicked() {

}

void DialogCreateAxiom::on_btnMoveUp_clicked() {

}

void DialogCreateAxiom::on_txtBoxName_textEdited(const QString& newName) {

}
