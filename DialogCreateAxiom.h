#ifndef DIALOG_CREATE_AXIOM_H
#define DIALOG_CREATE_AXIOM_H

#include <QDialog>

class LSystem;
class VariableSequence;
class VariableSequenceModel;

namespace Ui {
	class DialogCreateAxiom;
}

class DialogCreateAxiom : public QDialog {
	Q_OBJECT

public:
	enum Mode {
		CREATE,
		EDIT
	};

	explicit DialogCreateAxiom(LSystem* lSystem, QWidget *parent = 0);
	~DialogCreateAxiom();

	void setAxiom(VariableSequenceModel* sequenceModel);
	VariableSequence* getAxiom();

	void setMode(Mode mode);
	Mode getMode();

private slots:
	void on_btnAdd_clicked();
	void on_btnRemove_clicked();
	void on_btnMoveDown_clicked();
	void on_btnMoveUp_clicked();
	void on_txtBoxName_textEdited(const QString& name);

	void on_buttonBox_accepted();

private:
	Ui::DialogCreateAxiom* _ui;
	LSystem* _lSystem;
	VariableSequenceModel* _variableSequenceModel;
	VariableSequenceModel* _axiomVariableSequenceModel;

	Mode _mode;

	QString _originalName;

signals:
	void done();
	void cancel();
};

#endif // DIALOG_CREATE_AXIOM_H
