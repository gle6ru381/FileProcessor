#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

class ProgressDialog : public QDialog {
    Q_OBJECT
public:
    ProgressDialog(QWidget* parent = nullptr);
    ProgressDialog(Qt::WindowFlags flags, QWidget* parent = nullptr);
    ProgressDialog(QString const& title, QWidget* parent = nullptr);
    ProgressDialog(
            QString const& title,
            Qt::WindowFlags flags,
            QWidget* parent = nullptr);
};

#endif // PROGRESSDIALOG_H
