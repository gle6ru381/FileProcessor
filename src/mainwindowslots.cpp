#include "mainwindow.h"
#include "progressdialog.h"
#include <QApplication>
#include <QLabel>
#include <QMessageBox>

void MainWindow::changeMethod(int id)
{
    switch (id) {
    case 0: {
        if (!reserveVector->empty()) {
            if (showWarningChoise() == QMessageBox::Ok) {
                reserveVector->clear();
            } else {
                QButtonGroup* group = static_cast<QButtonGroup*>(sender());
                QAbstractButton* button = group->button(1);
                button->setChecked(true);
                break;
            }
        }
        choiseMethod = MethodReserve::FILE;
        break;
    }
    case 1: {
        QFile file("~temp.log");
        if (file.exists()) {
            if (showWarningChoise() == QMessageBox::Ok) {
                file.remove();
            } else {
                QButtonGroup* group = static_cast<QButtonGroup*>(sender());
                auto button = group->button(0);
                button->setChecked(true);
                break;
            }
        }
        choiseMethod = MethodReserve::VECTOR;
        break;
    }
    case 2: {
        QFile file("~temp.log");
        if (!reserveVector->empty()) {
            if (showWarningChoise() == QMessageBox::Ok) {
                reserveVector->clear();
            } else {
                auto group = static_cast<QButtonGroup*>(sender());
                auto button = group->button(1);
                button->setChecked(true);
                break;
            }
        } else if (file.exists()) {
            if (showWarningChoise() == QMessageBox::Ok) {
                file.remove();
            } else {
                auto group = static_cast<QButtonGroup*>(sender());
                auto button = group->button(0);
                button->setChecked(true);
                break;
            }
        }
        choiseMethod = MethodReserve::NONE;
        break;
    }
    }
}

using Bar = ProgressDialog::Bar;

void MainWindow::clickOk()
{
    insertDialog->hide();
    auto progDialog = new ProgressDialog(
            "Добавление файлов...",
            Qt::WindowTitleHint | Qt::WindowSystemMenuHint
                    | Qt::WindowTransparentForInput
                    | Qt::MSWindowsFixedSizeDialogHint);
    progDialog->show();
    progDialog->setAttribute(Qt::WA_DeleteOnClose);
    progDialog->setWindowFlags(
            progDialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    auto infos = pushInsert->selectedInfo();
    auto firstBar = new ProgressBar(0, infos.size(), nullptr, progDialog);
    firstBar->setFormat("%v из %m");
    firstBar->setLabel(new QLabel(""));
    progDialog->setBar(firstBar, Bar::First);

    int i = 0;

    for (auto info : infos) {
        firstBar->setName(info.fileName());
        firstBar->setValue(i);
        i++;

        mainWidget->addElement(&info, progDialog);
    }
    insertDialog->close();
    delete progDialog;
}

void MainWindow::selectBrowse(QFileInfo* info)
{
    mainWidget->addElement(info, nullptr);
    insertDialog->close();
}

void MainWindow::clickCancel()
{
    insertDialog->close();
}

void MainWindow::clickBrowse()
{
    insertDialog = new QDialog(
            this,
            Qt::WindowTitleHint | Qt::WindowSystemMenuHint
                    | Qt::WindowCloseButtonHint);
    insertDialog->setMaximumSize(400, 600);
    insertDialog->setMinimumSize(400, 600);
    insertDialog->setAttribute(Qt::WA_DeleteOnClose);
    auto style = insertStyleSheet();
    insertDialog->setStyleSheet(style.first);
    pushInsert = new PushInsert(insertDialog);
    QVBoxLayout* layout = new QVBoxLayout(insertDialog);
    QHBoxLayout* buttonLayout = new QHBoxLayout(insertDialog);
    QPushButton* ok = new QPushButton("Ок", insertDialog);
    QPushButton* cancel = new QPushButton("Отмена", insertDialog);

    pushInsert->setStyleSheet(style.second);

    connect(pushInsert,
            SIGNAL(selectIndex(QFileInfo*)),
            this,
            SLOT(selectBrowse(QFileInfo*)));
    connect(ok, SIGNAL(clicked()), this, SLOT(clickOk()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(clickCancel()));

    layout->addWidget(pushInsert);
    buttonLayout->addWidget(ok);
    buttonLayout->addWidget(cancel);
    layout->addLayout(buttonLayout);
    insertDialog->setLayout(layout);
    insertDialog->resize(400, 500);
    insertDialog->exec();
}

void MainWindow::mask_buttons()
{
    QPushButton* button = (QPushButton*)sender();
    mask->setText(mask->text() + button->text());
}

void MainWindow::clickRollback()
{
    if (choiseMethod == MethodReserve::FILE) {
        QFile oldNames("~temp.log");
        if (!oldNames.open(QIODevice::ReadOnly | QIODevice::Text)) {
            showError("Не удалось открыть файл для восстановления");
            return;
        }
        reset(oldNames, false);
    } else if (choiseMethod == MethodReserve::VECTOR) {
        try {
            reset(false);
        } catch (ExceptionReplacing except) {
            showError(except.error);
            return;
        }
    } else {
        showError("Откат выключен");
    }
}
