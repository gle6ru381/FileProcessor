#include "mainwidget.h"
#include <QDateTime>
#include <QDropEvent>
#include <QFileInfo>

MainWidget::MainWidget(QWidget* parent) : QTableWidget(parent)
{
    QStringList headers;
    headers << "Имя"
            << "Расположение"
            << "Дата изменения";
    this->setHorizontalHeaderLabels(headers);
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
        int row = this->rowCount();
        QFileInfo file = url.toLocalFile();

        this->insertRow(row);
        this->setItem(row, 0, new QTableWidgetItem(file.fileName()));
        this->setItem(row, 1, new QTableWidgetItem(file.filePath()));
        this->setItem(
                row, 2, new QTableWidgetItem(file.lastModified().toString()));
    }

    event->acceptProposedAction();
}
