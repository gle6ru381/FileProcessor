#ifndef PUSHINSERT_H
#define PUSHINSERT_H

#include <QFileSystemModel>
#include <QTreeView>

class PushInsert : public QTreeView { //Класс дерева системы, которое вызывается
                                      //при нажатии "Обзор..."
    Q_OBJECT
private:
    QFileSystemModel* model; //Модель системы

public:
    PushInsert(QWidget* parent = nullptr);
    QFileInfoList selectedInfo() const;

public slots:
    //Вызывается при двойном нажатии на файл и вызывает selectIndex
    void selectInfo(const QModelIndex& index);
signals:
    void selectIndex(QFileInfo*); //Передает информацию о файле
};

#endif // PUSHINSERT_H
