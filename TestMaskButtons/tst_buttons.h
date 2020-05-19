#ifndef TST_BUTTONS_H
#define TST_BUTTONS_H
#include <QtTest>

class buttons : public QObject {
    Q_OBJECT

public:
    buttons();
    ~buttons();

private slots:
    void test_data();
    void test_case1();
};
#endif // TST_BUTTONS_H
