#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
// Исключение файлов
class ExceptionFile {
public:
    QString error;
    ExceptionFile(QString const& error);
};

// Исключение переименования
class ExceptionReplacing {
public:
    QString error;
    ExceptionReplacing(QString const& error);
};

// Исключение обработки маск
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
