#ifndef MASK_H
#define MASK_H

#include <QObject>
#include <QString>

class Mask {
public:
    Mask(QString name, QString expand, QString mask);

private:
    QString const name;
    QString const expand;
    QString fullMask;
    QString totalName;

    void readName();
    void readMask(QString mask);
    void maskN(QString mask);
    void maskE(QString mask);
    void maskYMD(QString mask);

public:
    QString getTotalName() const;
};

#endif // MASK_H
