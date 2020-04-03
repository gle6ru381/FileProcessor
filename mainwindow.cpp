#include "mainwindow.h"
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    mask = new QLineEdit(this);
    QLabel* labMask = new QLabel("Маска имени", this);
    find = new QLineEdit(this);
    replace = new QLineEdit(this);
    QLabel* labFind = new QLabel("Найти", this);
    QLabel* labReplace = new QLabel("Заменить", this);
    layout->addWidget(mask, 0, 0);
    layout->addWidget(labMask, 1, 0);
    layout->addWidget(find, 0, 1);
    layout->addWidget(replace, 0, 2);
    layout->addWidget(labFind, 1, 1);
    layout->addWidget(labReplace, 1, 2);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}
