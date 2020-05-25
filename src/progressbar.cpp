#include "progressbar.h"
#include <QApplication>

/* В этом файле содержится реализация индикатора прогресса для добавления файлов
 */

ProgressBar::ProgressBar(QWidget* parent) : QProgressBar(parent)
{
    labelName = nullptr;
}

ProgressBar::ProgressBar(QLabel* label, QWidget* parent) : QProgressBar(parent)
{
    labelName = label;
}

ProgressBar::ProgressBar(QString const& name, QWidget* parent)
    : QProgressBar(parent)
{
    labelName = new QLabel(name, this);
}

ProgressBar::ProgressBar(int min, int max, QLabel* label, QWidget* parent)
    : ProgressBar(label, parent)
{
    this->setRange(min, max);
}

// Установка значения индикатора
void ProgressBar::setValue(int val)
{
    QProgressBar::setValue(val);
    QApplication::processEvents(
            QEventLoop::ExcludeUserInputEvents
            | QEventLoop::ExcludeSocketNotifiers);
}

// Возвращает имя индикатора
QString ProgressBar::name() const
{
    return labelName->text();
}

// Возвращает указатель на подпись с именем индикатора
QLabel* ProgressBar::label() const
{
    return labelName;
}

// Устанавливает имя индикатора
void ProgressBar::setName(const QString& name)
{
    if (!labelName)
        labelName = new QLabel(this);
    labelName->setText(name);
}

// Устанавливает новую подпись
void ProgressBar::setLabel(QLabel* label)
{
    if (labelName)
        delete labelName;
    labelName = label;
    label->setParent(this);
}
