#include "mainwidget.h"
#include <QDateTime>
#include <QDropEvent>
#include <QFileInfo>
#include <QHeaderView>

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
        addElement(info);
        delete info;
    }

    event->acceptProposedAction();
}

void MainWidget::addElement(QFileInfo* file)
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

    std::function<void(QDir*)> insertDir = [&, insert](QDir* dir) {
        foreach (
                auto file,
                dir->entryInfoList(
                        QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files)) {
            if (file.isFile())
                insert(&file);
            else {
                QDir* subDir = new QDir(file.absoluteFilePath());
                insertDir(subDir);
                delete subDir;
            }
        }
    };

    if (file->isDir()) {
        QDir* dir = new QDir(file->absoluteFilePath());
        insertDir(dir);
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

QFileInfoList MainWidget::files()
{
    QFileInfoList files;
    for (int i = 0; i < rowCount(); i++) {
        files.push_back(item(i, 2)->text());
    }
    return files;
}
