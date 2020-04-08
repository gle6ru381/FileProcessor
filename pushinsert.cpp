#include "pushinsert.h"

PushInsert::PushInsert(QWidget* parent) : QTreeView(parent)
{
    model = new QFileSystemModel(this);
    model->setRootPath("");
    setModel(model);
    hideColumn(1);
    hideColumn(2);
    setColumnWidth(0, 250);

    connect(this,
            SIGNAL(doubleClicked(const QModelIndex&)),
            this,
            SLOT(setRootIndex(const QModelIndex&)));
}

void PushInsert::setRootIndex(const QModelIndex& index)
{
    QTreeView::setRootIndex(index);
}
