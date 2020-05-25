#include "mainwindow.h"
#include <QRadioButton>

/* Этот файл содержит функции инициализации виджетов главного окна */

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

void MainWindow::buttonGroupInit()
{
    auto group = new QButtonGroup(this); // Создаем объект для логики кнопок
    auto file = new QRadioButton("файл", this);
    file->setToolTip("Данные для отката сохраняются в файле");
    auto vector = new QRadioButton("память", this);
    vector->setToolTip("Дланные для отката сохраняются в оперативной памяти");
    auto none = new QRadioButton("не сохранять", this);
    none->setToolTip("Отключение резервирования данных");

    file->setChecked(true);
    group->addButton(file, 0);
    group->addButton(vector, 1);
    group->addButton(none, 2);

    // Создаем объект для графического отображения кнопок
    method = new QGroupBox("Метод резервирования", this);
    auto layout = new QVBoxLayout(method);
    layout->addWidget(file);
    layout->addWidget(vector);
    layout->addWidget(none);
    method->setLayout(layout);

    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(changeMethod(int)));
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
    mN->setToolTip("Полное имя файла без расширения.");
    mNn->setToolTip(
            "Возвращает n-ый символ из имени файла. Пример: [N1] возвращает "
            "первый символ имени файла.");
    mNxy->setToolTip(
            "Возвращает часть имени файла от x и до y. Пример: [N2-5] "
            "возвращает строку, начиная со второго символа и заканчивая "
            "пятым.");
    mNnn->setToolTip(
            "Возвращает все символы из имени начиная с n-ого. Пример: [N2-] "
            "возвращает имя файла, начиная со второго символа.");
    mNpn->setToolTip(
            "Возвращает n-ый символ с конца строки. Пример: [N-5] возвращает 5 "
            "символ с конца.");
    mNxan->setToolTip(
            "Возвращает n символов из имени файла начиная с x. Пример: [N2,6] "
            "возвращает 6 символов начиная со второго.");
    mNnpy->setToolTip(
            "Возвращает строку, начиная с n-ого символа и заканчивая y c конца "
            "строки. Пример: [N2--5] возвращает часть имени начиная вторым "
            "символом и заканчивая пятым с конца.");
    mCn->setToolTip(
            "Возвращает увеличивающееся число или букву начиная с n с шагом "
            "1.");
    mCna->setToolTip(
            "Возвращает увеличивающееся число или букву начиная с n с шагом "
            "a.");
    mYMD->setToolTip(
            "Возвращает строку, содержащую дату последнего изменения файла в "
            "формате год, месяц, день.");
    mHMS->setToolTip(
            "Возвращает строку, содержащую дату последнего изменения файла в "
            "формате час, минуты, секунды.");
    mE->setToolTip("Возвращает расширение файла.");
    mExy->setToolTip("Возвращает расширение файла от x до y.");

    connect(mN, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mNn, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mNxy, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mNnn, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mNpn, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mNxan, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mNnpy, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mCn, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mCna, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mYMD, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mHMS, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mE, SIGNAL(clicked()), this, SLOT(mask_buttons()));
    connect(mExy, SIGNAL(clicked()), this, SLOT(mask_buttons()));
}
