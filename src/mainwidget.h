#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "pushinsert.h"
#include <QDir>
#include <QMimeData>
#include <QTableWidget>

class MainWidget : public QTableWidget { //Класс основного виджета с файлами
    Q_OBJECT
public:
    MainWidget(QWidget* parent = nullptr);
    void addElement(QFileInfo*); //Функция добавление файлов в виджет

private:
    void dropEvent(QDropEvent*) override;
    void dragLeaveEvent(QDragLeaveEvent*) override;
    void dragEnterEvent(QDragEnterEvent*) override;
    void dragMoveEvent(QDragMoveEvent*) override;
    //Функции для добавления файлов перетаскиванием мыши
public slots:
    void clearContents(); //Функция отчистки виджета
};

#endif // MAINWIDGET_H
