#include "mainwindow.h"
#include <QErrorMessage>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPalette>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    exception = false;
    this->setAcceptDrops(true);
    QGridLayout* layout = new QGridLayout(this);
    mask = new QLineEdit(this);
    QLabel* labMask = new QLabel("Маска имени", this);
    find = new QLineEdit(this);
    replace = new QLineEdit(this);
    QLabel* labFind = new QLabel("Найти", this);
    QLabel* labReplace = new QLabel("Заменить", this);

    fandr = new QPushButton("Найти и заменить", this);
    rollback = new QPushButton("Откат", this);
    fandr->setObjectName("mainButton");
    rollback->setObjectName("mainButton");
    connect(fandr, SIGNAL(clicked()), this, SLOT(readText()));

    layout->addWidget(mask, 0, 0);
    layout->addWidget(labMask, 1, 0, Qt::AlignTop);
    layout->addWidget(find, 0, 1);
    layout->addWidget(replace, 0, 2);

    buttonMaskInit();

    mainWidget = new MainWidget(this);

    mainWidget->setStyleSheet(
            "QHeaderView::section {background-color: #F4F4F4; border-style: "
            "none; border-bottom: 1px outset #E5E5E5; font-size: 14px; "
            "border-right: 2px outset #E7E7E7;} "
            "QHeaderView::section:checked {font-weight: normal;}"
            "QHeaderView {background-color: #F5F5F5;}");
    layout->addWidget(mainWidget, 3, 1, 3, 3);
    layout->addWidget(clear, 6, 1);

    connect(clear, SIGNAL(clicked()), mainWidget, SLOT(clearContents()));

    QVBoxLayout* fandrLayout = new QVBoxLayout(this);
    fandrLayout->addWidget(labReplace);
    fandrLayout->addWidget(fandr);

    QVBoxLayout* rollbackLayout = new QVBoxLayout(this);
    rollbackLayout->addWidget(labFind);
    rollbackLayout->addWidget(rollback);

    QVBoxLayout* maskLayout = new QVBoxLayout(this);
    QFrame* maskFrame = new QFrame;

    buttonLayoutInit(maskLayout, maskFrame);

    browse = new QPushButton("Обзор...", this);
    browse->setObjectName("mainButton");
    connect(browse, SIGNAL(clicked()), this, SLOT(clickBrowse()));

    layout->addWidget(browse, 6, 2);
    layout->addWidget(maskFrame, 3, 0);

    layout->addLayout(fandrLayout, 1, 2, Qt::AlignTop);
    layout->addLayout(rollbackLayout, 1, 1, Qt::AlignTop);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    initStyleSheet();
    this->resize(800, 600);
}

void MainWindow::buttonMaskInit()
{
    mN = new QPushButton("[N]", this);
    mN->setObjectName("maskButton");
    mNn = new QPushButton("[Nn]", this);
    mNn->setObjectName("maskButton");
    mNxy = new QPushButton("[Nx-y]", this);
    mNxy->setObjectName("maskButton");
    mNnn = new QPushButton("[Nn-]", this);
    mNnn->setObjectName("maskButton");
    mNpn = new QPushButton("[N-n]", this);
    mNpn->setObjectName("maskButton");
    mNxan = new QPushButton("[Nx,n]", this);
    mNxan->setObjectName("maskButton");
    mNnpy = new QPushButton("[Nn--y]", this);
    mNnpy->setObjectName("maskButton");
    mCn = new QPushButton("[Cn]", this);
    mCn->setObjectName("maskButton");
    mCna = new QPushButton("[Cn,a]", this);
    mCna->setObjectName("maskButton");
    mYMD = new QPushButton("[YMD]", this);
    mYMD->setObjectName("maskButton");
    mHMS = new QPushButton("[hms]", this);
    mHMS->setObjectName("maskButton");
    mE = new QPushButton("[E]", this);
    mE->setObjectName("maskButton");
    mExy = new QPushButton("[Ex-y]", this);
    mExy->setObjectName("maskButton");
    clear = new QPushButton("Очистить", this);
    clear->setObjectName("mainButton");
}

void MainWindow::buttonLayoutInit(QVBoxLayout* maskLayout, QFrame* maskFrame)
{
    maskFrame->setLayout(maskLayout);
    maskFrame->setObjectName("maskButtonFrame");
    maskFrame->setFrameStyle(QFrame::Raised);
    maskFrame->setFrameShape(QFrame::StyledPanel);
    maskLayout->addWidget(mN);
    maskLayout->addWidget(mNn);
    maskLayout->addWidget(mNxy);
    maskLayout->addWidget(mNnn);
    maskLayout->addWidget(mNpn);
    maskLayout->addWidget(mNxan);
    maskLayout->addWidget(mNnpy);
    maskLayout->addWidget(mCn);
    maskLayout->addWidget(mCna);
    maskLayout->addWidget(mYMD);
    maskLayout->addWidget(mHMS);
    maskLayout->addWidget(mE);
    maskLayout->addWidget(mExy);
}

void MainWindow::initStyleSheet()
{
    this->setStyleSheet(
            "QPushButton#maskButton {border-style: "
            "outset; border-width: 3px; border-color: #9C9C9C; padding: 10px; "
            "background-color: #EEEEEE; border-radius: 15px;} "
            "QPushButton#maskButton:pressed {border-style: ridge; "
            "border-width: 2px; background-color: #E3E3E3;} "
            "QPushButton#mainButton {background-color: qlineargradient(x1:0, "
            "y1:0, x2:1, y2:1, stop: 0 #DADADA, "
            "stop: 0.52 WhiteSmoke, stop: 0.97 #DADADA); border-style: none; "
            "padding: 7px;} "
            "QPushButton#mainButton:hover {background-color: "
            "qlineargradient(x1:0, "
            "y1:0, x2:1, y2:1, stop: 0 #CFCFCF, "
            "stop: 0.52 WhiteSmoke, stop: 0.97 #CFCFCF);} "
            "QPushButton#mainButton:pressed {background-color: "
            "qlineargradient(x1:0, y1:0, x2:1, y2:1, stop: 0 #EAEAEA, "
            "stop: 0.52 #DADADA, stop: 0.97 #EAEAEA);} "
            "QFrame#maskButtonFrame {background-color: #E6E6E6; border: 1px; "
            "border-radius: 3px; "
            "border-style: inset; border-width: 2px; "
            "border-color: #c0c0c0;} "
            "QLabel {font-size: 13px} "
            "QLineEdit {border: 2px #BFBFBF; border-radius: 3px; "
            "border-style: inset; border-width: 2px; "
            "selection-background-color: gray; background-color: #FEFEFE;} "
            "MainWidget {border: 2px Gainsboro; border-radius: 3px;"
            "border-style: inset; selection-background-color: "
            "qlineargradient(x1:0, y1:0, x2:0, y2:2, stop: 0 Gainsboro, stop: "
            "0.25 white, stop: 0.5 Gainsboro); selection-color: black; "
            "background-color: #F7F7F7; text-align: center;} ");
}
void MainWindow::readText()
{
    QString strMask = mask->text();
    QString strFind = find->text();
    QString strReplace = replace->text();

    try {
        if (strMask.contains(QRegExp("\\S*[\\/\\\\:\\*\\?\\|\\<\\>]\\S*"))) {
            throw 1;
        }
        if (strFind.contains(
                    QRegExp("\\S*[\\/\\\\\\:\\*\\?\\|\\<\\>\\[\\]]\\S*"))) {
            throw 2;
        }
        if (strReplace.contains(
                    QRegExp("\\S*[\\/\\\\\\:\\*\\?\\|\\<\\>\\[\\]]\\S*"))) {
            throw 3;
        }
        if (strReplace.isEmpty()) {
            throw 4;
        }
        if (strMask.isEmpty()) {
            throw 5;
        }

        Mask mask(strReplace, strMask);
        mask.readName();
        exception = false;
        replacing(mask, strFind);
    } catch (int a) {
        exception = true;
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        QString error;
        switch (a) {
        case 1: {
            error = QString("Строка маски имеет запрещенные символы");
            break;
        }
        case 2: {
            error = QString("Строка поиска имеет запрещенные символы");
            break;
        }
        case 3: {
            error = QString("Строка замены имеет запрещенные символы");
            break;
        }
        case 4: {
            error = QString("Строка замены не должна быть пуста");
            break;
        }
        case 5: {
            error = QString("Строка маски не должна быть пуста");
            break;
        }
        case -1: {
            error = QString("Открывающих скобок больше чем закрывающих");
            break;
        }
        case -2: {
            error = QString("Закрывающих скобок больше чем открывающих");
        }
        }
        dialog->setText(error);
        dialog->exec();
    } catch (ExceptionMask exp) {
        exception = true;
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setStyleSheet("align=center");
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        QString errorString("Ошибка в ");
        errorString += exp.mask;
        if (exp.type == TypeError::Number) {
            errorString += ": некорректное число";
        } else {
            errorString += ": некорректная маска";
        }
        if (!exp.expected.isEmpty()) {
            errorString += ". Ожидается " + exp.expected;
        }
        dialog->setText(errorString);

        dialog->exec();
    }
    if (exception)
        return;
}
void MainWindow::clickBrowse()
{
    insertDialog = new QDialog(this);
    insertDialog->setAttribute(Qt::WA_DeleteOnClose);
    insertDialog->setStyleSheet(
            "QPushButton {background-color: "
            "#EAEAEA; border: 2px outset "
            "#A1A1A1; padding: 5px;} "
            "QPushButton:pressed {background-color: #E5E5E5; border: 1px "
            "ridge "
            "#A1A1A1;} "
            "PushInsert {border: 2px inset #A1A1A1; border-radius: 3px;}");
    pushInsert = new PushInsert(insertDialog);
    QVBoxLayout* layout = new QVBoxLayout(insertDialog);
    QHBoxLayout* buttonLayout = new QHBoxLayout(insertDialog);
    QPushButton* ok = new QPushButton("Ок", insertDialog);
    QPushButton* cancel = new QPushButton("Отмена", insertDialog);

    pushInsert->setStyleSheet(
            "QHeaderView::section {background-color: #F0F0F0;} "
            "QHeaderView {background-color: #F0F0F0;} "
            "background-color: #F0F0F0;");

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

void MainWindow::selectBrowse(QFileInfo* info)
{
    mainWidget->addElement(info);
    insertDialog->close();
}

void MainWindow::clickOk()
{
    for (auto info : pushInsert->selectedInfo()) {
        mainWidget->addElement(&info);
    }
    insertDialog->close();
}

void MainWindow::clickCancel()
{
    insertDialog->close();
}

MainWindow::~MainWindow()
{
}
