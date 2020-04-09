#ifndef MASK_H
#define MASK_H

#include <QObject>
#include <QString>

class Mask {
    Q_OBJECT
public:
    Mask(QString name, QString expand, QString mask);

private:
    QString const name;
    QString const expand;
    QString mask;
    QString totalName;

    void readName();
    void readMask(QString mask);
};

#endif // MASK_H
