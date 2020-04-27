#include "mask.h"

Mask::Mask(QString name, QString mask) : name(name), fullMask(mask)
{
}

ExceptionMask::ExceptionMask(
        TypeError const type, QString const mask, QString const expected)
    : type(type), mask(mask), expected(expected)
{
}

static int fullMaskIndex = 0;

void Mask::readName()
{
    for (int nameIndex = 0; nameIndex < fullMask.size(); nameIndex++) {
        fullMaskIndex = nameIndex;
        QString mask;
        if (fullMask.at(nameIndex) == '[') {
            while (fullMask.at(++nameIndex) != ']') {
                mask += fullMask.at(nameIndex);
            }
            readMask(mask);
        } else {
            totalName += fullMask.at(nameIndex);
        }
    }
}

void Mask::readMask(QString mask)
{
    switch (mask.at(0).unicode()) {
    case 'N': {
        if (mask.size() == 1)
            totalName += name;
        else
            maskN(mask.remove(0, 1));
        return;
    }
    case 'E': {
        if (mask.size() == 1)
            totalName += "/E/";
        else
            maskE(mask.remove(0, 1));
        return;
    }
    case 'Y':
    case 'M':
    case 'D': {
        maskYMD(mask);
        return;
    }
    case 'h':
    case 'm':
    case 's': {
        maskHMS(mask);
        return;
    }
    case 'C': {
        if (mask.size() == 1) {
            totalName += "/C" + QString::number(stepValue.size()) + "/";
            stepValue.push_back(1);
            beginValue.push_back(1);
        } else {
            maskC(mask.remove(0, 1));
        }
    }
    }
}

void Mask::maskN(QString mask)
{
    if (mask.endsWith('-')) {
        QString totalNumber;
        for (int i = 0; i < mask.size() - 1; i++) {
            if (mask.at(i).isNumber())
                totalNumber += mask.at(i);
            else
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[Nn-] начиная с ") + fullMaskIndex);
        }
        int Index = totalNumber.toInt() - 1;
        if (Index > name.size())
            throw ExceptionMask(
                    TypeError::Number,
                    QString("[Nn-] начиная с ") + fullMaskIndex,
                    QString("не больше ") + name.size());
        for (int i = Index; i < name.size(); i++) {
            totalName += name.at(i);
        }
        return;
    } else if (mask.at(0) == '-') {
        QString totalNumber;
        for (int i = 1; i < mask.size(); i++) {
            if (mask.at(i).isNumber())
                totalNumber += mask.at(i);
            else
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[N-n] начиная с ") + fullMaskIndex);
            ;
        }
        int diff = totalNumber.toInt() + 1;
        if (diff - 1 > name.size())
            throw ExceptionMask(
                    TypeError::Number,
                    QString("[N-n] начиная с ") + fullMaskIndex,
                    QString("не больше ") + name.size());
        for (int i = name.size() - diff; i < name.size(); i++) {
            totalName += name.at(i);
        }
        return;
    } else if (mask.contains("--")) {
        QString number[2];
        int choise = 0;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c.isNumber()) {
                number[choise] += c;
            } else if (c == '-') {
                if (choise == 1)
                    throw ExceptionMask(
                            TypeError::Semantic,
                            QString("[Nn--y] начиная с ") + fullMaskIndex);
                if (mask.at(++i) == '-') {
                    i++;
                    choise = 1;
                } else {
                    throw ExceptionMask(
                            TypeError::Semantic,
                            QString("[Nn--y] начиная с ") + fullMaskIndex);
                }
            } else
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[Nn--y] начиная с ") + fullMaskIndex);
        }
        if (number[0].isEmpty() || number[1].isEmpty()) {
            throw ExceptionMask(
                    TypeError::Semantic,
                    QString("[Nn--y] начиная с ") + fullMaskIndex);
        }
        int first = number[0].toInt() - 1;
        int second = number[1].toInt();
        if (first > name.size() || second > name.size())
            throw ExceptionMask(
                    TypeError::Number,
                    QString("[Nn--y] начиная с ") + fullMaskIndex,
                    QString("не больше ") + name.size());
        int diff = name.size() - second;

        for (int i = first; i < diff; i++) {
            totalName += name.at(i);
        }
        return;
    } else if (mask.contains('-')) {
        QString number[2];
        int choise = 0;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c.isNumber()) {
                number[choise] += c;
            } else if (c == '-') {
                if (choise == 1)
                    throw ExceptionMask(
                            TypeError::Semantic,
                            QString("[Nx-y] начиная с ") + fullMaskIndex);
                choise = 1;
            } else
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[Nx-y] начиная с ") + fullMaskIndex);
        }
        if (number[0].isEmpty() || number[1].isEmpty()) {
            throw ExceptionMask(
                    TypeError::Semantic,
                    QString("[Nx-y] начиная с ") + fullMaskIndex);
        }

        int first = number[0].toInt() - 1;
        int second = number[1].toInt() - 1;
        if (first > second || second >= name.size())
            throw ExceptionMask(
                    TypeError::Number,
                    QString("[Nx-y] начиная с ") + fullMaskIndex,
                    QString("не больше ") + name.size());
        for (int i = first; i <= second; i++) {
            totalName += name.at(i);
        }
        return;
    } else if (mask.contains(',')) {
        QString number[2];
        int choise = 0;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c.isNumber()) {
                number[choise] += c;
            } else if (c == ',') {
                if (choise == 1)
                    throw ExceptionMask(
                            TypeError::Semantic,
                            QString("[Nx,y] начиная с ") + fullMaskIndex);
                choise = 1;
            } else {
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[Nx,y] начиная с ") + fullMaskIndex);
            }
        }
        if (number[0].isEmpty() || number[1].isEmpty()) {
            throw ExceptionMask(
                    TypeError::Semantic,
                    QString("[Nx,y] начиная с ") + fullMaskIndex);
        }

        int first = number[0].toInt() - 1;
        int second = number[1].toInt() + first;

        if (first > name.size() || second > name.size()) {
            throw ExceptionMask(
                    TypeError::Number,
                    QString("[Nx,y] начиная с ") + fullMaskIndex,
                    QString("не больше ") + name.size());
        }
        for (int i = first; i < second; i++) {
            totalName += name.at(i);
        }

        return;
    } else {
        QString number;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c.isNumber()) {
                number += c;
            } else {
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[Nn] начиная с ") + fullMaskIndex);
            }
        }
        int index = number.toInt() - 1;
        if (index > name.size())
            throw ExceptionMask(
                    TypeError::Number,
                    QString("[Nn] начиная с ") + fullMaskIndex,
                    QString("не больше ") + name.size());
        totalName += name.at(index);
    }
}

void Mask::maskE(QString mask)
{
    if (!mask.contains('-')) {
        throw ExceptionMask(
                TypeError::Semantic,
                QString("[Ex-y] начиная с ") + fullMaskIndex);
    } else {
        QString number[2];
        int choise = 0;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c.isNumber()) {
                number[choise] += c;
            } else if (c == '-') {
                if (choise == 1)
                    throw ExceptionMask(
                            TypeError::Semantic,
                            QString("[Ex-y] начиная с ") + fullMaskIndex);
                choise = 1;
            } else
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[Ex-y] начиная с ") + fullMaskIndex);
        }
        totalName += QString("/En") + number[0] + "-" + number[1] + '/';
    }
}

void Mask::maskYMD(QString mask)
{
    if (!mask.endsWith('Y') && !mask.endsWith('M') && !mask.endsWith('D'))
        throw ExceptionMask(
                TypeError::Semantic,
                QString("[YMD] начиная с ") + fullMaskIndex);
    bool findY = false;
    bool findM = false;
    bool findD = false;
    for (int i = 0; i < mask.size(); i++) {
        QChar c = mask.at(i);
        if (c == 'Y') {
            if (findY)
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[YMD] начиная с ") + fullMaskIndex);

            totalName += '/' + c + '/';
            findY = true;
        } else if (c == 'M') {
            if (findM)
                ExceptionMask(
                        TypeError::Semantic,
                        QString("[YMD] начиная с ") + fullMaskIndex);

            totalName += '/' + c + '/';
            findM = true;
        } else if (c == 'D') {
            if (findD)
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[YMD] начиная с ") + fullMaskIndex);

            totalName += '/' + c + '/';
            findD = true;
        } else {
            totalName += c;
        }
    }
}

void Mask::maskHMS(QString mask)
{
    if (!mask.endsWith('h') && !mask.endsWith('s') && !mask.endsWith('m'))
        throw ExceptionMask(
                TypeError::Semantic,
                QString("[hms] начиная с ") + fullMaskIndex);

    bool findH = false;
    bool findM = false;
    bool findS = false;

    for (int i = 0; i < mask.size(); i++) {
        QChar c = mask.at(i);
        if (c == 'h') {
            if (findH)
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[hms] начиная с ") + fullMaskIndex);

            totalName += '/' + c + '/';
            findH = true;
        } else if (c == 's') {
            if (findS)
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[hms] начиная с ") + fullMaskIndex);

            totalName += '/' + c + '/';
            findS = true;
        } else if (c == 'm') {
            if (findM)
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[hms] начиная с ") + fullMaskIndex);

            totalName += '/' + c + '/';
            findM = true;
        } else {
            totalName += c;
        }
    }
}

void Mask::maskC(QString mask)
{
    if (!mask.at(0).isNumber())
        throw ExceptionMask(
                TypeError::Semantic, QString("[C] начиная с ") + fullMaskIndex);

    if (mask.contains(',')) {
        QString number[2];
        int choise = 0;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c.isNumber()) {
                number[choise] += c;
            } else if (c == ',') {
                if (choise == 1)
                    throw ExceptionMask(
                            TypeError::Semantic,
                            QString("[Cn,a] начиная с ") + fullMaskIndex);
                choise = 1;
            } else
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[C] начиная с ") + fullMaskIndex);
        }
        uint totalStep = number[1].toUInt();
        if (totalStep == 0)
            throw ExceptionMask(
                    TypeError::Number,
                    QString("[Nn] начиная с ") + fullMaskIndex,
                    QString("шаг больше нуля"));
        totalName += "/C" + QString::number(stepValue.size()) + "/";
        beginValue.push_back(number[0].toUInt());
        stepValue.push_back(totalStep);
        return;
    } else {
        QString number;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c.isNumber())
                number += c;
            else
                throw ExceptionMask(
                        TypeError::Semantic,
                        QString("[C] начиная с ") + fullMaskIndex);
        }

        totalName += "/C" + QString::number(stepValue.size()) + "/";
        beginValue.push_back(number.toUInt());
        stepValue.push_back(1);
        return;
    }
}

inline QString Mask::getTotalName() const
{
    return totalName;
}

inline uint Mask::Count_C() const
{
    return stepValue.size();
}

uint Mask::getValue_C(uint index)
{
    uint value = beginValue.at(index);
    beginValue[index] += stepValue[index];
    return value;
}
