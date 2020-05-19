#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "exception.h"
#include "mainwidget.h"
#include "mask.h"
#include "pushinsert.h"
#include <QButtonGroup>
#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QVector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    enum class MethodReserve { FILE, VECTOR, NONE };
    MethodReserve choiseMethod; //Метож резервирования
    QLineEdit* mask;            // Строка маски
    QLineEdit* find;            // Строка найти
    QLineEdit* replace;         // строка заменить
    QPushButton* fandr; // Переменные кнопок с масками
    QPushButton* rollback;
    QPushButton* mN;
    QPushButton* mNn;
    QPushButton* mNxy;
    QPushButton* mNnn;
    QPushButton* mNpn;
    QPushButton* mNxan;
    QPushButton* mNnpy;
    QPushButton* mCn;
    QPushButton* mCna;
    QPushButton* mYMD;
    QPushButton* mHMS;
    QPushButton* mE;
    QPushButton* mExy;
    QPushButton* browse;
    QPushButton* clear;
    QGroupBox* method; // 3 кнопки с методами резервирования
    MainWidget* mainWidget; // Виджет с кнопками для переименования
    PushInsert* pushInsert; // Дерево системы
    QDialog* insertDialog;  // Окно "Обзор..."
    QVector<QString>* reserveVector; // Массив резервированных данных
    bool exception;
    // Функции инициализации
    void buttonMaskInit();
    void buttonLayoutInit(QVBoxLayout* layout, QFrame* frame);
    void initStyleSheet();
    void buttonGroupInit();
    QString widgetStyleSheet();
    std::pair<QString, QString> insertStyleSheet();
    //Функции переименования
    void renameProcess(QFile& reserve, Mask& mask, QString& oldName);
    void renameProcess(QVector<QString>& reserve, Mask& mask, QString& oldName);
    void renameProcess(Mask& mask, QString& oldName);
    void replacing(Mask& mask, QString& oldName);
    void replacingTemplate(QString& name, Mask& mask, QFileInfo& file);
    //Функции отката
    void reset(QFile& file, bool error);

private slots:
    void mask_buttons(); // Функция действия для кнопок масок

public slots:
    void clickBrowse(); //Нажатие на "Обзор..."
    void selectBrowse(QFileInfo*); //Сюда передается selectIndex из PushInsert
    void clickOk();                //Нажатие на Ок в доп.окне
    void clickCancel(); //Нажатие на Отмена в доп.окне
    void readText(); // Считывание текста из полей "Маска", "Найти" и "Заменить"
    void changeMethod(int id); // Переключение метода резервирования
    void clickRollback(); // Нажатие на откат
};
#endif // MAINWINDOW_H
