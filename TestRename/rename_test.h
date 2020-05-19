#ifndef RENAME_TEST_H
#define RENAME_TEST_H
#include <QVector>
#include <QtTest>
#include <QtTestGui>
#define TEST

class renameTest : public QObject {
    Q_OBJECT

public:
    QString beginName;
    renameTest();
    ~renameTest();

private slots:
    void test_rename_data();
    void test_rename();
    void compare_name(QString const& totalName);
};

#endif // RENAME_TEST_H
