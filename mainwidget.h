#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "pushinsert.h"
#include <QDir>
#include <QMimeData>
#include <QTableWidget>

class MainWidget : public QTableWidget {
    Q_OBJECT
public:
    MainWidget(QWidget* parent = nullptr);

private:
    PushInsert* pushInsert;
    void dropEvent(QDropEvent*) override;
    void dragLeaveEvent(QDragLeaveEvent*) override;
    void dragEnterEvent(QDragEnterEvent*) override;
    void dragMoveEvent(QDragMoveEvent*) override;
};

#endif // MAINWIDGET_H
