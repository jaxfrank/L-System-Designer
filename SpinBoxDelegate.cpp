#include "SpinBoxDelegate.h"

#include <limits>

#include <QSpinBox>

SpinBoxDelegate::SpinBoxDelegate(QObject *parent) :
	QItemDelegate(parent)
{
}


QWidget*SpinBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QSpinBox* editor = new QSpinBox(parent);
	editor->setMinimum(0);
	editor->setMaximum(std::numeric_limits<int>::max());

	return editor;
}

void SpinBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
	int value = index.model()->data(index, Qt::EditRole).toInt();
	QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
	QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
	model->setData(index, QVariant::fromValue<int>(spinBox->value()), Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	editor->setGeometry(option.rect);
}
