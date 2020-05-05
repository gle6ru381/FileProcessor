#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"
#include "mask.h"
#include "pushinsert.h"
#include <QDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QLineEdit* mask;
    QLineEdit* find;
    QLineEdit* replace;
    QPushButton* fandr;
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
    MainWidget* mainWidget;
    PushInsert* pushInsert;
    QDialog* insertDialog;
    bool exception;

    void buttonMaskInit();
    void buttonLayoutInit(QVBoxLayout* layout, QFrame* frame);
    void initStyleSheet();
    void replacing(Mask& mask, QString oldName);
    void reset(QFile&);

public slots:
    void clickBrowse(); //Нажатие на "Обзор..."
    void selectBrowse(QFileInfo*); //Сюда передается selectIndex из PushInsert
    void clickOk();                //Нажатие на Ок в доп.окне
    void clickCancel(); //Нажатие на Отмена в доп.окне
    void readText(); // Считывание текста из полей "Маска", "Найти" и "Заменить"
};
#endif // MAINWINDOW_H
