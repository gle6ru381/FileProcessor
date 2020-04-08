#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"
#include "pushinsert.h"
#include <QDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

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
    MainWidget* mainWidget;
    PushInsert* pushInsert;
    QDialog* insertDialog;

public slots:
    void clickBrowse();
    void selectBrowse(QFileInfo*);
    void clickOk();
    void clickCancel();
};
#endif // MAINWINDOW_H
