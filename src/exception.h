#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

class ExceptionFile {
public:
    QString error;
    ExceptionFile(QString& error);
};

class ExceptionReplacing {
public:
    QString error;
    ExceptionReplacing(QString& error);
};

#endif // EXCEPTION_H
