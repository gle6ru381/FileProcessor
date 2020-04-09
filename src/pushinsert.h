#ifndef PUSHINSERT_H
#define PUSHINSERT_H

#include <QFileSystemModel>
#include <QTreeView>

class PushInsert : public QTreeView {
    Q_OBJECT
private:
    QFileSystemModel* model;

public:
    PushInsert(QWidget* parent = nullptr);
    QFileInfoList selectedInfo() const;

public slots:
    void selectInfo(const QModelIndex& index);

signals:
    void selectIndex(QFileInfo*);
};

#endif // PUSHINSERT_H
