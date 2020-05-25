#include "mainwidget.h"
#include <QApplication>
#include <QDateTime>
#include <QDropEvent>
#include <QFileInfo>
#include <QHeaderView>
#include <QLabel>
#include <QPair>
#include <QVBoxLayout>

/* Этот файл содержит реализацию класса MainWidget, который
   характеризует окно со всеми файлами для переименования и
   функции для добавления, изменения и извлечения файлов из таблицы
*/

MainWidget::MainWidget(QWidget* parent) : QTableWidget(parent)
{
    QStringList headers;
    headers << "Имя"
            << "Дата изменения"
            << "Местоположение";
    this->setColumnCount(3);
    this->setHorizontalHeaderLabels(headers);
    horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    this->setColumnWidth(0, 100);
    this->setColumnWidth(1, 140);
    this->setColumnWidth(2, 275);
    this->setAcceptDrops(true);
    this->verticalHeader()->hide();
}

using Bar = ProgressDialog::Bar;

void MainWidget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (!mimeData->hasUrls())
        return;

    auto progDialog = new ProgressDialog("Добавление файлов...");
    progDialog->show();
    auto urls = mimeData->urls();
    auto firstBar = new ProgressBar(0, urls.size(), nullptr, progDialog);
    firstBar->setFormat("%v из %m");
    firstBar->setLabel(new QLabel(""));
    progDialog->setBar(firstBar, Bar::First);
    int i = 0;

    for (QUrl url : mimeData->urls()) {
        if (url.scheme() != "file") {
            continue;
        }
        QFileInfo* info = new QFileInfo(url.toLocalFile());

        firstBar->setName(info->fileName());
        firstBar->setValue(i++);

        addElement(info, progDialog);
        delete info;
    }

    event->acceptProposedAction();
}

void MainWidget::addElement(QFileInfo* file, ProgressDialog* progDialog)
{
    // Лямбда добавления отдельного файла
    auto insert = [this](QFileInfo* file) {
        int row = this->rowCount();
        this->insertRow(row);
        this->setRowHeight(row, 30);
        this->setItem(row, 0, new QTableWidgetItem(file->fileName()));
        this->setItem(
                row,
                1,
                new QTableWidgetItem(
                        file->lastModified().toString(Qt::ISODate)));
        this->setItem(row, 2, new QTableWidgetItem(file->filePath()));
    };

    // Лямбда добавления директории
    std::function<void(QDir*)> insertDir = [&, insert, progDialog](QDir* dir) {
        auto bar = progDialog->bar(Bar::Second);
        auto files = dir->entryInfoList(
                QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
        bar->setRange(0, files.size() + 1);
        int i = 0;

        foreach (auto file, files) {
            bar->setValue(i);
            i++;

            if (file.isFile())
                insert(&file);
            else {
                QDir* subDir = new QDir(file.absoluteFilePath());

                progDialog->setBar(
                        new ProgressBar(
                                new QLabel("Добавление " + file.fileName()),
                                progDialog),
                        Bar::Second);

                insertDir(subDir);

                bar = new ProgressBar(
                        new QLabel("Добавление " + dir->dirName()), progDialog);
                progDialog->setBar(bar, Bar::Second);

                delete subDir;
            }
        }
    };

    // Вызов лямбд в зависимости от типа файла
    if (file->isDir()) {
        QDir* dir = new QDir(file->absoluteFilePath());

        progDialog->setBar(
                new ProgressBar(
                        new QLabel("Добавление " + file->fileName()),
                        progDialog),
                Bar::Second);

        insertDir(dir);

        delete dir;
    } else {
        insert(file);
    }

    this->resizeColumnsToContents();
}

// Функции для реализации добавления элементов с помощью мыши
void MainWidget::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void MainWidget::dragMoveEvent(QDragMoveEvent* event)
{
    event->acceptProposedAction();
}

void MainWidget::dragEnterEvent(QDragEnterEvent* event)
{
    event->acceptProposedAction();
}

void MainWidget::clearContents()
{
    setRowCount(0);
}

// Функция для изменения значения таблицы в определенной строке
void MainWidget::changeTable(QFileInfo const& file, int row)
{
    auto itemName = new QTableWidgetItem(file.fileName());
    auto itemDate
            = new QTableWidgetItem(file.lastModified().toString(Qt::ISODate));
    auto itemPath = new QTableWidgetItem(file.absoluteFilePath());

    setItem(row, 0, itemName);
    setItem(row, 1, itemDate);
    setItem(row, 2, itemPath);
}
