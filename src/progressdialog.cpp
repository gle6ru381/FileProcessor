#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget* parent) : QDialog(parent)
{
    bars = qMakePair(nullptr, nullptr);
    setLayout(new QVBoxLayout(this));
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

inline QVBoxLayout* ProgressDialog::layout() const
{
    return static_cast<QVBoxLayout*>(QDialog::layout());
}

void ProgressDialog::setBar(ProgressBar* const bar, Bar choise)
{
    if (choise == Bar::First) {
        auto layout = this->layout();
        if (bars.first) {
            layout->replaceWidget(bars.first->label(), bar->label());
            layout->replaceWidget(bars.first, bar);
            delete bars.first;
        } else {
            layout->addWidget(bar->label());
            layout->addWidget(bar);
        }
        bars.first = bar;
    } else {
        auto layout = this->layout();
        if (bars.second) {
            layout->replaceWidget(bars.second->label(), bar->label());
            layout->replaceWidget(bars.second, bar);
            delete bars.second->label();
            delete bars.second;
        } else {
            layout->addWidget(bar->label());
            layout->addWidget(bar);
        }
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
