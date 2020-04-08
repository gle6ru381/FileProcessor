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

public slots:
    void setRootIndex(const QModelIndex& index) override;
};

#endif // PUSHINSERT_H
