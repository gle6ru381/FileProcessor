#ifndef MASK_H
#define MASK_H

#include <QObject>
#include <QString>
#include <QVector>

class Mask {
public:
    Mask(QString name, QString expand, QString mask);

private:
    QString const name;
    QString const expand;
    QString fullMask;
    QString totalName;
    QVector<uint> stepValue;
    QVector<uint> beginValue;

    void readName();
    void readMask(QString mask);
    void maskN(QString mask);
    void maskE(QString mask);
    void maskYMD(QString mask);
    void maskHMS(QString mask);
    void maskC(QString mask);

public:
    QString getTotalName() const;
    uint Count_C() const;
    uint getValue_C(uint index);
};

#endif // MASK_H
