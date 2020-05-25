#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget* parent) : QDialog(parent)
{
    bars = qMakePair(nullptr, nullptr);
}

ProgressDialog::ProgressDialog(Qt::WindowFlags flags, QWidget* parent)
    : ProgressDialog(parent)
{
    setWindowFlags(flags);
}

ProgressDialog::ProgressDialog(QString const& title, QWidget* parent)
    : ProgressDialog(parent)
{
    setWindowTitle(title);
}

ProgressDialog::ProgressDialog(
        QString const& title, Qt::WindowFlags flags, QWidget* parent)
    : ProgressDialog(parent)
{
    setWindowTitle(title);
    setWindowFlags(flags);
}

void ProgressDialog::setBar(ProgressBar* const bar, Bar choise)
{
    if (choise == Bar::First) {
        bars.first = bar;
    } else {
        bars.second = bar;
    }
}

ProgressBar* ProgressDialog::bar(Bar choise) const
{
    if (choise == Bar::First) {
        return bars.first;
    } else {
        return bars.second;
    }
}

void ProgressDialog::removeBar(Bar choise)
{
    if (choise == Bar::First) {
        if (!bars.first)
            return;
        delete bars.first;
        bars.first = nullptr;
    } else {
        if (!bars.second)
            return;
        delete bars.second;
        bars.second = nullptr;
    }
}
