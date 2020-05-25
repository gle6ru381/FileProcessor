#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget* parent) : QDialog(parent)
{
}

ProgressDialog::ProgressDialog(Qt::WindowFlags flags, QWidget* parent)
    : QDialog(parent)
{
    setWindowFlags(flags);
}

ProgressDialog::ProgressDialog(QString const& title, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(title);
}

ProgressDialog::ProgressDialog(
        QString const& title, Qt::WindowFlags flags, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(title);
    setWindowFlags(flags);
}
