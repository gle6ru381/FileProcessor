#ifndef RENAME_TEST_H
#define RENAME_TEST_H
#include <QtTest>
#include <QtTestGui>

class renameTest : public QObject {
    Q_OBJECT

public:
    renameTest();
    ~renameTest();

private slots:
    void test_rename_data();
    void test_rename();
};

#endif // RENAME_TEST_H
