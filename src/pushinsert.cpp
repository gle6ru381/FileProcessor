#include "pushinsert.h"
#include <QHeaderView>

/* В этом файле содержится реализация класса PushInsert
Этот клас характеризует дерево системы, которое появляется при нажатии на кнопку
"Обзор..." и позволяет добавлять файлы для переименования.
*/
PushInsert::PushInsert(QWidget* parent) : QTreeView(parent)
{
    model = new QFileSystemModel(this);
    model->setRootPath("");
    setModel(model);
    hideColumn(1); // Скрытие ненужных столбцов
    hideColumn(2);
    setColumnWidth(0, 250);

    // Замена заголовка имени
    QHeaderView* header = this->header();
    header->setSectionsMovable(false);
    header->setSectionResizeMode(QHeaderView::Fixed);
    this->setHeader(header);

    connect(this,
            SIGNAL(doubleClicked(const QModelIndex&)),
            this,
            SLOT(selectInfo(const QModelIndex&)));
}

// Возвращает QFileInfo выбранного файла
void PushInsert::selectInfo(const QModelIndex& index)
{
    QFileInfo* info = new QFileInfo(model->filePath(index));

    emit selectIndex(info);
}

// Возвращает QFileInfo Всех файлов
QFileInfoList PushInsert::selectedInfo() const
{
    auto indexes = selectedIndexes();
    QFileInfoList infoList;
    for (auto index : indexes) {
        infoList.push_back(model->filePath(index));
    }
    return infoList;
}
