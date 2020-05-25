#include "progressbar.h"
#include <QApplication>

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

void ProgressBar::setValue(int val)
{
    QProgressBar::setValue(val);
    QApplication::processEvents(
            QEventLoop::ExcludeUserInputEvents
            | QEventLoop::ExcludeSocketNotifiers);
}

QString ProgressBar::name() const
{
    return labelName->text();
}

QLabel* ProgressBar::label() const
{
    return labelName;
}

void ProgressBar::setName(const QString& name)
{
    if (!labelName)
        labelName = new QLabel(this);
    labelName->setText(name);
}

void ProgressBar::setLabel(QLabel* label)
{
    if (labelName)
        delete labelName;
    labelName = label;
    label->setParent(this);
}
