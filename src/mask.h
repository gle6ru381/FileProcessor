#ifndef MASK_H
#define MASK_H

#include "exception.h"
#include <QString>
#include <QVector>

class Mask { //Класс для обработки масок
public:
    Mask(QString name, QString mask);

private:
    enum class UsingsMasks : uint64_t {
        None = 0,
        Mask_C = 1,
        Mask_E = 1 << 1,
        Mask_Y = 1 << 2,
        Mask_M = 1 << 3,
        Mask_D = 1 << 4,
        Mask_h = 1 << 5,
        Mask_m = 1 << 6,
        Mask_s = 1 << 7
    };
    UsingsMasks masks;
    QString const name;      //Имя для замены
    QString fullMask;        //Полная маска файла
    QString totalName;       //Итоговое имя
    QVector<uint> stepValue; //Массив, хранящий значение шагов для шаблона [C]
    QVector<uint> beginValue; //Массив, хранящий значения чисел для подстановки
                              //для шаблона [C]
    //функции прочтения отдельных масок
    void readMask(QString& mask);
    void maskN(QString& mask);
    void maskE(QString& mask);
    void maskYMD(QString& mask);
    void maskHMS(QString& mask);
    void maskC(QString& mask);
    void checkBracketBalance();

public:
    void readName(); //Основныя функция прочтения имени
    QString getTotalName() const; //Возвращает итоговое имя
    uint Count_C() const; //Возвращает число шаблонов [C] в общем шаблоне
    QString area() const; // Возвращает имя для замены (name)
    uint getValue_C(uint index); //Возвращает и увеличиввает значение счетчика
                                 //по индексу
};

#endif // MASK_H
