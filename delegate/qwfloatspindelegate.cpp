#include "qwfloatspindelegate.h"
#include <QDoubleSpinBox>

QWFloatSpinDelegate::QWFloatSpinDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *QWFloatSpinDelegate::createEditor(QWidget *                   parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &         index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(10000);
    return editor;
}

void QWFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    double          value   = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox *>(editor);
    spinBox->setValue(value);
}

void QWFloatSpinDelegate::setModelData(QWidget *           editor,
                                       QAbstractItemModel *model,
                                       const QModelIndex & index) const {
    QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
    spinBox->interpretText();
    double value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWFloatSpinDelegate::updateEditorGeometry(QWidget *                   editor,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex &         index) const {
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
