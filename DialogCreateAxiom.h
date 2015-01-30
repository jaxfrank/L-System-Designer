#ifndef DIALOG_CREATE_AXIOM_H
#define DIALOG_CREATE_AXIOM_H

#include <QDialog>

namespace Ui {
	class DialogCreateAxiom;
}

class DialogCreateAxiom : public QDialog {
	Q_OBJECT

public:
	explicit DialogCreateAxiom(QWidget *parent = 0);
	~DialogCreateAxiom();

private slots:
	void on_btnAdd_clicked();

	void on_btnRemove_clicked();

	void on_btnMoveDown_clicked();

	void on_btnMoveUp_clicked();

private:
	Ui::DialogCreateAxiom* _ui;
};

#endif // DIALOG_CREATE_AXIOM_H
