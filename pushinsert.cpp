#include "pushinsert.h"

PushInsert::PushInsert(QWidget* parent) : QTreeView(parent)
{
    model = new QFileSystemModel(this);
    model->setRootPath("");

    connect(this,
            SIGNAL(doubleClicked(const QModelIndex&)),
            this,
            SLOT(setRootIndex(const QModelIndex&)));
}
