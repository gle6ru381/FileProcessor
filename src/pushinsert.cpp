#include "pushinsert.h"
#include <QHeaderView>

PushInsert::PushInsert(QWidget* parent) : QTreeView(parent)
{
    model = new QFileSystemModel(this);
    model->setRootPath("");
    setModel(model);
    hideColumn(1);
    hideColumn(2);
    setColumnWidth(0, 250);
    QHeaderView* header = this->header();
    header->setSectionsMovable(false);
    header->setSectionResizeMode(QHeaderView::Fixed);
    this->setHeader(header);

    connect(this,
            SIGNAL(doubleClicked(const QModelIndex&)),
            this,
            SLOT(selectInfo(const QModelIndex&)));
}

void PushInsert::selectInfo(const QModelIndex& index)
{
    QFileInfo* info = new QFileInfo(model->filePath(index));

    emit selectIndex(info);
}

QFileInfoList PushInsert::selectedInfo() const
{
    auto indexes = selectedIndexes();
    QFileInfoList infoList;
    for (auto index : indexes) {
        infoList.push_back(model->filePath(index));
    }
    return infoList;
}
