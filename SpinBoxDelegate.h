#ifndef SPIN_BOX_DELEGATE_H
#define SPIN_BOX_DELEGATE_H

#include <QItemDelegate>

class SpinBoxDelegate : public QItemDelegate {
	Q_OBJECT
public:
	explicit SpinBoxDelegate(QObject *parent = 0);

	QWidget*createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	void setEditorData(QWidget* editor, const QModelIndex& index) const;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};

#endif // SPIN_BOX_DELEGATE_H
