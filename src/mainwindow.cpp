#include "mainwindow.h"
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QProgressDialog>

/* Этот файл содержит реализацию основного окна приложения,
   а также обработку событий всех кнопок.
*/

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    reserveVector = new QVector<QString>;
    choiseMethod = MethodReserve::FILE;
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
    connect(rollback, SIGNAL(clicked()), this, SLOT(clickRollback()));

    layout->addWidget(mask, 0, 0);
    layout->addWidget(labMask, 1, 0, Qt::AlignTop);
    layout->addWidget(find, 0, 1);
    layout->addWidget(replace, 0, 2);

    buttonMaskInit();
    buttonGroupInit();

    mainWidget = new MainWidget(this);

    mainWidget->setStyleSheet(widgetStyleSheet());
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

    QVBoxLayout* leftLayout = new QVBoxLayout(this);
    leftLayout->addWidget(method);
    leftLayout->addWidget(maskFrame);

    browse = new QPushButton("Обзор...", this);
    browse->setObjectName("mainButton");
    connect(browse, SIGNAL(clicked()), this, SLOT(clickBrowse()));

    layout->addWidget(browse, 6, 2);
    layout->addLayout(leftLayout, 3, 0);

    layout->addLayout(fandrLayout, 1, 2, Qt::AlignTop);
    layout->addLayout(rollbackLayout, 1, 1, Qt::AlignTop);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    initStyleSheet();

    this->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    this->setMaximumSize(800, 860);
    this->setMinimumSize(800, 860);
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
        if (strFind.isEmpty()) {
            throw 6;
        }
        Mask mask(strReplace, strMask);
        mask.readName();
        replacing(mask, strFind);
    } catch (int a) {
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        QString error;
        switch (a) {
        case 1: {
            error = QString("Строка \"маска\" имеет запрещенные символы");
            break;
        }
        case 2: {
            error = QString("Строка \"найти\" имеет запрещенные символы");
            break;
        }
        case 3: {
            error = QString("Строка \"заменить\" имеет запрещенные символы");
            break;
        }
        case 4: {
            error = QString("Строка \"заменить\" не должна быть пуста");
            break;
        }
        case 5: {
            error = QString("Строка \"маска\" не должна быть пуста");
            break;
        }
        case 6: {
            error = QString("Строка \"найти\" не должна быть пуста");
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
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setStyleSheet("align=center");
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        QString errorString("Ошибка в ");
        errorString += exp.mask;
        if (exp.type == ExceptionMask::TypeError::Number) {
            errorString += ": некорректное число";
        } else {
            errorString += ": некорректная маска";
        }
        if (!exp.expected.isEmpty()) {
            errorString += ". Ожидается " + exp.expected;
        }
        dialog->setText(errorString);

        dialog->exec();
    } catch (ExceptionFile exp) {
        showError(exp.error);
    } catch (ExceptionReplacing exp) {
        QMessageBox* dialog = new QMessageBox(this);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setText(exp.error);
        if (choiseMethod != MethodReserve::NONE)
            dialog->setInformativeText("Все изменения отменены");
        else
            dialog->setInformativeText("Часть файлов переименована");
        dialog->exec();
    }
}

void MainWindow::showError(QString const& errorText)
{
    QMessageBox* error = new QMessageBox(this);
    error->setAttribute(Qt::WA_DeleteOnClose);
    error->setText(errorText);
    error->exec();
    return;
}

int MainWindow::showWarningChoise()
{
    auto warning = new QMessageBox(this);
    warning->setAttribute(Qt::WA_DeleteOnClose);
    warning->setText(
            "При переключении метода резервирования старые данные "
            "будут потеряны и откат будет не доступен.");
    warning->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    return warning->exec();
}

MainWindow::~MainWindow()
{
    QFile("~temp.log").remove();
}
