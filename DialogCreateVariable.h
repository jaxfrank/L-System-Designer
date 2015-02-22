#ifndef DIALOG_CREATE_VARIABLE
#define DIALOG_CREATE_VARIABLE

#include <QDialog>
#include <QModelIndex>

#include "VariableSequenceModel.h"
#include "SpinBoxDelegate.h"

class LSystem;

namespace Ui {
	class DialogCreateVariable;
}

class DialogCreateVariable : public QDialog {
	Q_OBJECT

signals:
	void done();
	void cancel();

public:
	enum Mode {
		EDIT,
		CREATE
	};

	explicit DialogCreateVariable(LSystem* lSystem, QWidget *parent = 0);
	~DialogCreateVariable();

	void setVariable(Variable* variable);
	Variable* getVariable();

	void setMode(Mode mode);
	Mode getMode() const;

private slots:
	void on_btnAddToProduction_clicked();
	void on_btnRemoveFromProduction_clicked();

	void on_btnAddProduction_clicked();
	void on_btnRemoveProduction_clicked();

	void on_productionsView_clicked(const QModelIndex &index);

	void on_btnBoxOkCancel_accepted();
	void on_btnBoxOkCancel_rejected();

	void on_txtProductionName_textEdited(const QString &arg1);

	void on_txtVarName_textEdited(const QString &arg1);

private:
	Ui::DialogCreateVariable* _ui;
	LSystem* _lSystem;
	Variable* _variable;
	QString _originalName;
	VariableSequenceModel* _variableModel;
	SpinBoxDelegate* _itemDelegate;

	VariableSequenceModel* _currentProductionModel;
	QModelIndex _currentProductionIndex;

	Mode _currentMode;

};

#endif // DIALOG_CREATE_VARIABLE
