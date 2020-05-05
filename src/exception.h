#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class ExceptionFile {
public:
    QString error;
    ExceptionFile(QString const& error);
};

class ExceptionReplacing {
public:
    QString error;
    ExceptionReplacing(QString const& error);
};

struct ExceptionMask {
    enum class TypeError { Semantic, Number };
    TypeError const type;
    QString const mask;
    QString const expected;

    ExceptionMask(
            TypeError const& type,
            QString const& mask,
            QString const& expected = "\0");
};

#endif // EXCEPTION_H
