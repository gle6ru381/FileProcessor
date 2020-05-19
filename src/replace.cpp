#include "mainwindow.h"
#include <QDateTime>
#include <QTextStream>

using Pair = std::pair<QString, int>;

Pair convertE(QChar const* format, QString const extension)
{
    QString numbers[2];
    int size = 4;
    short choise = 0;
    for (int i = 0; format[i] != '/'; i++) {
        if (format[i] == '-') {
            choise = 1;
            size++;
            continue;
        }
        numbers[choise].push_back(format[i]);
        size++;
    }
    QString total;
    int numberOne = numbers[0].toInt() - 1;
    int numberTwo = numbers[1].toInt() - 1;
    while (numberOne <= numberTwo) {
        total += extension[numberOne];
        numberOne++;
    }
    return std::make_pair(total, size);
}

Pair convertC(QChar const* format, Mask& mask)
{
    QString index;
    int size = 3;
    for (int i = 0; format[i] != '/'; i++) {
        index += format[i];
        size++;
    }
    uint n = mask.getValue_C(index.toInt());

    return std::make_pair(QString::number(n), size);
}

void MainWindow::reset(QFile& oldNames, bool error)
{
    QString name;
    for (int i = 0;; i++) {
        name = oldNames.readLine();
        name.remove('\n');
        if (name.isNull())
            break;
        QFileInfo file(mainWidget->item(i, 2)->text());
        QString newOldName = file.absolutePath() + '/' + name;
        QFile(file.absoluteFilePath()).rename(newOldName);
        mainWidget->changeTable(QFileInfo(newOldName), i);
    }
    oldNames.remove();
    if (error)
        throw ExceptionReplacing(
                "Один из файлов не существует, переименование прервано");
}

void MainWindow::replacing(Mask& mask, QString& replacingArea)
{
    auto date = [](QFileInfo info, QString type) {
        return info.lastModified().toString(type);
    };
    QFile temp("~temp.log");
    if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw ExceptionFile(
                "Невозможно создать файл для восстановления имен при "
                "ошибке");
    }
    QTextStream oldNames(&temp);
    for (int i = 0; i < mainWidget->rowCount(); i++) {
        QFileInfo file(mainWidget->item(i, 2)->text());
        if (!file.exists()) {
            temp.close();
            if (!temp.open(QIODevice::ReadOnly | QIODevice::Text)) {
                throw ExceptionFile(
                        "Невозможно прочитать файл для восстановления");
            }
            reset(temp, true);
            break;
        }
        QString newName(mask.getTotalName());
        QString totalName = file.fileName();
        oldNames << totalName << '\n';

        newName.replace("/Y/", date(file, "yyyy"));
        newName.replace("/M/", date(file, "MM"));
        newName.replace("/D/", date(file, "dd"));
        newName.replace("/h/", date(file, "hh"));
        newName.replace("/m/", date(file, "mm"));
        newName.replace("/s/", date(file, "ss"));
        newName.replace("/E/", file.suffix());

        while (newName.contains('/')) {
            int ind = newName.indexOf('/');
            switch (newName[ind + 1].unicode()) {
            case 'E': {
                auto pair = convertE(newName.data() + ind + 3, file.suffix());
                newName.replace(ind, pair.second, pair.first);
                break;
            }
            case 'C': {
                auto pair = convertC(newName.data() + ind + 2, mask);
                newName.replace(ind, pair.second, pair.first);
                break;
            }
            }
        }
        totalName.replace(replacingArea, newName);
        QString renaming(file.absolutePath() + '/' + totalName);
        QFile(file.absoluteFilePath()).rename(renaming);
        mainWidget->changeTable(QFileInfo(renaming), i);
    }
}
