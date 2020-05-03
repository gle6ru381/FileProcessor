#include "mainwindow.h"
#include <QDateTime>

void MainWindow::replacing(Mask mask)
{
    auto date = [](QFileInfo info, QString type) {
        return info.lastModified().toString(type);
    };
    for (QFileInfo& file : mainWidget->files()) {
        if (!file.exists()) {
            continue;
        }
        QString newName(mask.getTotalName());

        newName.replace("/Y/", date(file, "yy"));
        newName.replace("/M/", date(file, "MM"));
        newName.replace("/D/", date(file, "dd"));
        newName.replace("/h/", date(file, "hh"));
        newName.replace("/m/", date(file, "mm"));
        newName.replace("/s/", date(file, "ss"));
        newName.replace("/E/", file.suffix());
    }
}
