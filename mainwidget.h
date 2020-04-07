#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMimeData>
#include <QTableWidget>

class MainWidget : public QTableWidget {
    Q_OBJECT
public:
    MainWidget(QWidget* parent = nullptr);

private:
    void dropEvent(QDropEvent*);
};

#endif // MAINWIDGET_H
