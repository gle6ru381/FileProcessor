#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "pushinsert.h"
#include <QDir>
#include <QFile>
#include <QFileInfoList>
#include <QMimeData>
#include <QTableWidget>

class MainWidget : public QTableWidget { //Класс основного виджета с файлами
    Q_OBJECT
public:
    MainWidget(QWidget* parent = nullptr);
    void addElement(QFileInfo*); //Функция добавление файлов в виджет
    void changeTable(QFileInfo const& file, int row); //Изменение строки таблицы

private:
    //Функции для добавления файлов перетаскиванием мыши
    void dropEvent(QDropEvent*) override;
    void dragLeaveEvent(QDragLeaveEvent*) override;
    void dragEnterEvent(QDragEnterEvent*) override;
    void dragMoveEvent(QDragMoveEvent*) override;
public slots:
    void clearContents(); //Функция отчистки виджета
signals:
    void notOpen();
};

#endif // MAINWIDGET_H
