#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include "progressbar.h"
#include <QDialog>
#include <QPair>
#include <QVBoxLayout>

class ProgressDialog : public QDialog {
    Q_OBJECT
private:
    QPair<ProgressBar*, ProgressBar*> bars;

    inline QVBoxLayout* layout() const;

public:
    enum class Bar { First, Second };
    ProgressDialog(QWidget* parent = nullptr);
    ProgressDialog(Qt::WindowFlags flags, QWidget* parent = nullptr);
    ProgressDialog(QString const& title, QWidget* parent = nullptr);
    ProgressDialog(
            QString const& title,
            Qt::WindowFlags flags,
            QWidget* parent = nullptr);

    void setBar(ProgressBar* const bar, Bar choise);
    ProgressBar* bar(Bar choise) const;
    void removeBar(Bar choise);
};

#endif // PROGRESSDIALOG_H
