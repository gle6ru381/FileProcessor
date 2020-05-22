#include "mainwindow.h"
#include <QApplication>
#include <QDateTime>
#include <QProgressBar>
#include <QProgressDialog>
#include <QTextStream>

// В этом файле содержатся функции переименования файлов

using Pair = std::pair<QString, int>;

Pair convertE(QChar const* format, QString const extension)
{
    QString numbers[2]; // Первое и второе число в маске [Ex-y]
    int size = 4;     // Длина строки маски
    short choise = 0; // индекс читаемого числа
    for (int i = 0; format[i] != '/'; i++) { // считывание чисел
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
    QString index;                           // Индекс счетчика
    int size = 3;                            // Длина маски
    for (int i = 0; format[i] != '/'; i++) { // считывание индекса
        index += format[i];
        size++;
    }
    uint n = mask.getValue_C(
            index.toInt()); // Получение данных счетчика по индексу

    return std::make_pair(QString::number(n), size);
}

void MainWindow::reset(bool error) // Откат для Vector
{
    if (reserveVector->empty()) { // Если вектор пуст, бросаем исключение
        throw ExceptionReplacing("Нечего откатывать");
    }
    for (int i = 0; i < reserveVector->size(); i++) {
        QFileInfo file(mainWidget->item(i, 2)->text()); // Берем файл
        QString newOldName = file.absolutePath() + '/'
                + reserveVector->at(i); // старое имя
        QFile(file.absoluteFilePath()).rename(newOldName); // Переименовываем
        mainWidget->changeTable(QFileInfo(newOldName), i); // Изменяем таблицу
    }
    reserveVector->clear(); // Очищаем вектор
    if (error) // Если произошла ошибка то бросаем исключение
        throw ExceptionReplacing(
                "Один из файлов не существует, переименование прервано");
}

void MainWindow::reset(QFile& oldNames, bool error)
{
    QString name;
    for (int i = 0;; i++) {
        name = QString::fromUtf8(oldNames.readLine()); // Читаем строку из файла
        name.remove('\n');
        if (name.isNull()) // Проверка на NULL
            break;
        QFileInfo file(mainWidget->item(i, 2)->text()); // Создаем объект файла
        QString newOldName = file.absolutePath() + '/' + name; // старое имя
        QFile(file.absoluteFilePath()).rename(newOldName); // переименование
        mainWidget->changeTable(QFileInfo(newOldName), i); // изменяем таблицу
    }
    oldNames.remove(); // удаляем файл резерва
    if (error) // Если произошла ошибка бросаем исключение
        throw ExceptionReplacing(
                "Один из файлов не существует, переименование прервано");
}

void MainWindow::replacing(Mask& mask, QString& replacingArea)
{
    // В зависимости от метода резервирования выбираем нужную функцию
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
    // лямбда для получения даты файла
    auto date = [](QFileInfo info, QString type) {
        return info.lastModified().toString(type);
    };

    // Заменяем все шаблоны, разные для разных файлов
    name.replace("/Y/", date(file, "yyyy"));
    name.replace("/M/", date(file, "MM"));
    name.replace("/D/", date(file, "dd"));
    name.replace("/h/", date(file, "hh"));
    name.replace("/m/", date(file, "mm"));
    name.replace("/s/", date(file, "ss"));
    name.replace("/E/", file.suffix());

    // Заменяем расширение типа [E*] и счетчик
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
    QTextStream oldNames(&reserve); // Создаем поток для записи в файл
    oldNames.setCodec("UTF-8");
    QProgressDialog progressDialog(this);
    progressDialog.setRange(0, mainWidget->rowCount());
    progressDialog.setLabelText("Переименование...");
    QProgressBar bar;
    bar.setFormat("%v из %m");
    bar.setRange(0, mainWidget->rowCount());
    progressDialog.setBar(&bar);
    progressDialog.setCancelButton(nullptr);
    progressDialog.show();

    for (int i = 0; i < mainWidget->rowCount(); i++) {
        progressDialog.setValue(i);
        QApplication::processEvents();
        QFileInfo file(mainWidget->item(i, 2)->text()); // Создаем объект файла
        if (!file.exists()) { // Если файл не существует
            reserve.close();  // Открываем файл для чтения
            if (!reserve.open(QIODevice::ReadOnly | QIODevice::Text)) {
                throw ExceptionFile( // если файл не открылся бросаем исключение
                        "Невозможно прочитать файл для восстановления");
            }
            reset(reserve, true); // Вызываем откат с ошибкой
            break;
        }
        QString newName(mask.getTotalName()); // новое имя для части замены
        QString totalName = file.fileName(); // итоговое имя
        oldNames << totalName
                 << '\n'; // Записываем имя для резервирования в файл

        replacingTemplate(newName, mask, file); // Замена оставшихся шаблонов

        // Замена имени
        totalName.replace(replacingArea, newName);
        QString renaming(file.absolutePath() + '/' + totalName);
        QFile(file.absoluteFilePath()).rename(renaming);
        mainWidget->changeTable(QFileInfo(renaming), i); // Обновление таблицы
    }
    progressDialog.deleteLater();
}

void MainWindow::renameProcess(
        QVector<QString>& reserve, Mask& mask, QString& replacingArea)
{
    QProgressDialog progressDialog(this);
    progressDialog.setRange(0, mainWidget->rowCount());
    progressDialog.setLabelText("Переименование...");
    QProgressBar bar;
    bar.setFormat("%v из %m");
    bar.setRange(0, mainWidget->rowCount());
    progressDialog.setBar(&bar);
    progressDialog.setCancelButton(nullptr);
    progressDialog.show();

    for (int i = 0; i < mainWidget->rowCount(); i++) {
        progressDialog.setValue(i);
        QApplication::processEvents();
        QFileInfo file(mainWidget->item(i, 2)->text()); // Объект файла
        if (!file.exists()) { // Если файл не существует
            reset(true);      // Вызываем откат с ошибкой
        }
        QString newName(mask.getTotalName());
        QString totalName = file.fileName();
        reserve.push_back(
                totalName); // Записываем имя для резервирования в файл

        replacingTemplate(newName, mask, file); // Замена шаблонов

        // Замена имени
        totalName.replace(replacingArea, newName);
        QString renaming(file.absolutePath() + '/' + totalName);
        QFile(file.absoluteFilePath()).rename(renaming);
        mainWidget->changeTable(QFileInfo(renaming), i); // Обновление таблицы
    }
}

void MainWindow::renameProcess(Mask& mask, QString& replacingArea)
{
    QProgressDialog progressDialog(this);
    progressDialog.setRange(0, mainWidget->rowCount());
    progressDialog.setLabelText("Переименование...");
    QProgressBar bar;
    bar.setFormat("%v из %m");
    bar.setRange(0, mainWidget->rowCount());
    progressDialog.setBar(&bar);
    progressDialog.setCancelButton(nullptr);
    progressDialog.show();

    for (int i = 0; i < mainWidget->rowCount(); i++) {
        progressDialog.setValue(i);
        QApplication::processEvents();
        QFileInfo file(mainWidget->item(i, 2)->text()); // Объект байла
        if (!file.exists()) { // Если файл не существоет бросаем исключение
            throw ExceptionReplacing(
                    "Один из файлов не существует. Переименование прервано. "
                    "Файлы не восстановлены");
        }
        QString newName(mask.getTotalName());
        QString totalName = file.fileName();

        replacingTemplate(newName, mask, file); // Замена шаблонов

        // Замена имени
        totalName.replace(replacingArea, newName);
        QString renaming(file.absolutePath() + '/' + totalName);
        QFile(file.absoluteFilePath()).rename(renaming);
        mainWidget->changeTable(QFileInfo(renaming), i); // Обновление таблицы
    }
}
