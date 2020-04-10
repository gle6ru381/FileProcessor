#ifndef READMASK_TEST_H
#define READMASK_TEST_H
#include <QTest>

class ReadMask_Test : public QObject {
    Q_OBJECT

public:
    ReadMask_Test();
    ~ReadMask_Test();

private slots:
    void test_case1_data();
    void test_case1();
    void test_step_and_value();
    void test_step_and_value_data();
};

#endif // READMASK_TEST_H
