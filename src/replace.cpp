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
    if (choiseMethod == MethodReserve::FILE) {
        QFile temp("~temp.log");
        if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
            throw ExceptionFile(
                    "Невозможно создать файл для восстановления имен при "
                    "ошибке");
        }
        renameProcess(temp, mask, replacingArea);
    } else if (choiseMethod == MethodReserve::VECTOR) {
        if (!reserveVector->empty())
            reserveVector->clear();
        renameProcess(*reserveVector, mask, replacingArea);
    } else {
        renameProcess(mask, replacingArea);
    }
}

void MainWindow::replacingTemplate(QString& name, Mask& mask, QFileInfo& file)
{
    auto date = [](QFileInfo info, QString type) {
        return info.lastModified().toString(type);
    };

    name.replace("/Y/", date(file, "yyyy"));
    name.replace("/M/", date(file, "MM"));
    name.replace("/D/", date(file, "dd"));
    name.replace("/h/", date(file, "hh"));
    name.replace("/m/", date(file, "mm"));
    name.replace("/s/", date(file, "ss"));
    name.replace("/E/", file.suffix());

    while (name.contains('/')) {
        int ind = name.indexOf('/');
        switch (name[ind + 1].unicode()) {
        case 'E': {
            auto pair = convertE(name.data() + ind + 3, file.suffix());
            name.replace(ind, pair.second, pair.first);
            break;
        }
        case 'C': {
            auto pair = convertC(name.data() + ind + 2, mask);
            name.replace(ind, pair.second, pair.first);
            break;
        }
        }
    }
}

void MainWindow::renameProcess(
        QFile& reserve, Mask& mask, QString& replacingArea)
{
    QTextStream oldNames(&reserve);
    for (int i = 0; i < mainWidget->rowCount(); i++) {
        QFileInfo file(mainWidget->item(i, 2)->text());
        if (!file.exists()) {
            reserve.close();
            if (!reserve.open(QIODevice::ReadOnly | QIODevice::Text)) {
                throw ExceptionFile(
                        "Невозможно прочитать файл для восстановления");
            }
            reset(reserve, true);
            break;
        }
        QString newName(mask.getTotalName());
        QString totalName = file.fileName();
        oldNames << totalName << '\n';

        replacingTemplate(newName, mask, file);

        totalName.replace(replacingArea, newName);
        QString renaming(file.absolutePath() + '/' + totalName);
        QFile(file.absoluteFilePath()).rename(renaming);
        mainWidget->changeTable(QFileInfo(renaming), i);
    }
}

void MainWindow::renameProcess(
        QVector<QString>& reserve, Mask& mask, QString& replacingArea)
{
    for (int i = 0; i < mainWidget->rowCount(); i++) {
        QFileInfo file(mainWidget->item(i, 2)->text());
        if (!file.exists()) {
        }
        QString newName(mask.getTotalName());
        QString totalName = file.fileName();
        reserve.push_back(totalName);

        replacingTemplate(newName, mask, file);

        totalName.replace(replacingArea, newName);
        QString renaming(file.absoluteFilePath() + '/' + totalName);
        QFile(file.absoluteFilePath()).rename(renaming);
        mainWidget->changeTable(QFileInfo(renaming), i);
    }
}

void MainWindow::renameProcess(Mask& mask, QString& replacingArea)
{
    for (int i = 0; i < mainWidget->rowCount(); i++) {
        QFileInfo file(mainWidget->item(i, 2)->text());
        if (!file.exists()) {
        }
        QString newName(mask.getTotalName());
        QString totalName = file.fileName();

        replacingTemplate(newName, mask, file);

        totalName.replace(replacingArea, newName);
        QString renaming(file.absoluteFilePath() + '/' + totalName);
        QFile(file.absoluteFilePath()).rename(renaming);
        mainWidget->changeTable(QFileInfo(renaming), i);
    }
}
