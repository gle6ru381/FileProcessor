#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QLabel>
#include <QProgressBar>

class ProgressBar : public QProgressBar {
    Q_OBJECT
private:
    QLabel* labelName;

public:
    ProgressBar(QWidget* parent = nullptr);
    ProgressBar(QLabel* name, QWidget* parent = nullptr);
    ProgressBar(QString const& name, QWidget* parent = nullptr);
    ProgressBar(
            int min,
            int max,
            QLabel* name = nullptr,
            QWidget* parent = nullptr);

    void setValue(int val);
    QString name() const;
    void setName(QString const& name);
    QLabel* label() const;
    void setLabel(QLabel* label);
};

#endif // PROGRESSBAR_H
