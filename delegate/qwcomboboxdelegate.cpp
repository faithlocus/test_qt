#include "qwcomboboxdelegate.h"

#include <QComboBox>
QWComboboxDelegate::QWComboboxDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *QWComboboxDelegate::createEditor(QWidget *                   parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &         index) const {
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *editor = new QComboBox(parent);
    editor->setFrame(false);
    editor->addItem("1");
    editor->addItem("2");
    editor->addItem("3");
    return editor;
}

void QWComboboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString    value    = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    comboBox->setCurrentText(value);
}

void QWComboboxDelegate::setModelData(QWidget *           editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex & index) const {
    QComboBox *comboBox = static_cast<QComboBox *>(editor);
    QString    value    = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void QWComboboxDelegate::updateEditorGeometry(QWidget *                   editor,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &         index) const {
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
