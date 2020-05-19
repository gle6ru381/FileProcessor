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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    enum class MethodReserve { FILE, VECTOR, NONE };
    MethodReserve choiseMethod;
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
    QGroupBox* method;
    MainWidget* mainWidget;
    PushInsert* pushInsert;
    QDialog* insertDialog;
    bool exception;

    void buttonMaskInit();
    void buttonLayoutInit(QVBoxLayout* layout, QFrame* frame);
    void initStyleSheet();
    void buttonGroupInit();
    QString widgetStyleSheet();
    std::pair<QString, QString> insertStyleSheet();

    void replacing(Mask& mask, QString& oldName);
    void reset(QFile& file, bool error);

private slots:
    void mask_buttons();

public slots:
    void clickBrowse(); //Нажатие на "Обзор..."
    void selectBrowse(QFileInfo*); //Сюда передается selectIndex из PushInsert
    void clickOk();                //Нажатие на Ок в доп.окне
    void clickCancel(); //Нажатие на Отмена в доп.окне
    void readText(); // Считывание текста из полей "Маска", "Найти" и "Заменить"
    void changeMethod(int id);
    void clickRollback();
};
#endif // MAINWINDOW_H
