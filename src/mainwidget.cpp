#include "mainwidget.h"
#include <QApplication>
#include <QDateTime>
#include <QDropEvent>
#include <QFileInfo>
#include <QHeaderView>
#include <QLabel>
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

void MainWidget::dropEvent(QDropEvent* event)
{
    const QMimeData* mimeData = event->mimeData();

    if (!mimeData->hasUrls())
        return;
    for (QUrl url : mimeData->urls()) {
        if (url.scheme() != "file") {
            continue;
        }
        QFileInfo* info = new QFileInfo(url.toLocalFile());
        addElement(info, nullptr);
        delete info;
    }

    event->acceptProposedAction();
}

using Pair = std::pair<QProgressBar*, QLabel*>;

void setPair(QDialog* dialog, Pair& newPair, Pair& oldPair)
{
    auto layout = static_cast<QVBoxLayout*>(dialog->layout());
    layout->replaceWidget(oldPair.second, newPair.second);
    layout->replaceWidget(oldPair.first, newPair.first);
    delete oldPair.second;
    delete oldPair.first;
    dialog->setLayout(layout);
}

Pair changeProgBar(QDialog* dialog, QString const dirName)
{
    auto layout = static_cast<QVBoxLayout*>(dialog->layout());
    auto label = new QLabel("Добавление " + dirName);
    auto secondBar = new QProgressBar;

    layout->addWidget(label);
    layout->addWidget(secondBar);

    return std::make_pair(secondBar, label);
}

void removePair(QDialog* dialog, Pair& pair)
{
    auto layout = static_cast<QVBoxLayout*>(dialog->layout());
    layout->removeWidget(pair.first);
    layout->removeWidget(pair.second);
    delete pair.first;
    delete pair.second;
    dialog->setLayout(nullptr);
    dialog->update();
    QApplication::processEvents();
    dialog->setLayout(layout);
    dialog->update();
    QApplication::processEvents();
}

void MainWidget::addElement(QFileInfo* file, QDialog* progDialog)
{
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

    std::function<void(QDir*, Pair)> insertDir = [&, insert, progDialog](
                                                         QDir* dir, Pair pair) {
        auto bar = pair.first;
        auto files = dir->entryInfoList(
                QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
        bar->setRange(0, files.size());
        int i = 0;

        foreach (auto file, files) {
            bar->setValue(i);
            QApplication::processEvents();
            i++;

            if (file.isFile())
                insert(&file);
            else {
                QDir* subDir = new QDir(file.absoluteFilePath());

                auto newPair = changeProgBar(progDialog, file.fileName());

                removePair(progDialog, pair);

                insertDir(subDir, newPair);

                auto oldPair = changeProgBar(progDialog, dir->dirName());
                bar = pair.first = oldPair.first;
                pair.second = oldPair.second;
                setPair(progDialog, oldPair, newPair);

                delete subDir;
            }
        }
    };

    if (file->isDir()) {
        QDir* dir = new QDir(file->absoluteFilePath());

        auto pair = changeProgBar(progDialog, file->fileName());
        QApplication::processEvents();

        insertDir(dir, pair);

        delete dir;
    } else {
        insert(file);
    }

    this->resizeColumnsToContents();
}

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
