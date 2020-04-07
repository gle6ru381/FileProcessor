#include "mainwindow.h"
#include "mainwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    mask = new QLineEdit(this);
    QLabel* labMask = new QLabel("Маска имени", this);
    find = new QLineEdit(this);
    replace = new QLineEdit(this);
    QLabel* labFind = new QLabel("Найти", this);
    QLabel* labReplace = new QLabel("Заменить", this);
    fandr = new QPushButton("Найти и заменить", this);
    rollback = new QPushButton("Откат", this);
    layout->addWidget(mask, 0, 0);
    layout->addWidget(labMask, 1, 0, Qt::AlignTop);
    layout->addWidget(find, 0, 1);
    layout->addWidget(replace, 0, 2);
    layout->addWidget(labFind, 1, 1, Qt::AlignTop);
    layout->addWidget(labReplace, 1, 2, Qt::AlignTop);
    layout->addWidget(fandr, 2, 1);
    layout->addWidget(rollback, 2, 2);

    mN = new QPushButton("[N]", this);
    mNn = new QPushButton("[Nn]", this);
    mNxy = new QPushButton("[Nx-y]", this);
    mNnn = new QPushButton("[Nn-]", this);
    mNpn = new QPushButton("[N-n]", this);
    mNxan = new QPushButton("[Nx,n]", this);
    mNnpy = new QPushButton("[Nn--y]", this);
    mCn = new QPushButton("[Cn]", this);
    mCna = new QPushButton("[Cn,a]", this);
    mYMD = new QPushButton("[YMD]", this);
    mHMS = new QPushButton("[hms]", this);
    mE = new QPushButton("[E]", this);
    mExy = new QPushButton("[Ex-y]", this);

    QVBoxLayout* maskLayout = new QVBoxLayout(this);
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
    layout->addLayout(maskLayout, 3, 0);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}
