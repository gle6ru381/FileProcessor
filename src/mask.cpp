#include "mask.h"

Mask::Mask(QString name, QString expand, QString mask)
    : name(name), expand(expand), fullMask(mask)
{
    readName();
}

void Mask::readName()
{
    for (int i = 0; i < fullMask.size(); i++) {
        if (fullMask.at(i) == '[') {
            QString mask;
            while (fullMask.at(++i) != ']') {
                mask += fullMask.at(i);
            }
            readMask(mask);
        } else {
            totalName += fullMask.at(i);
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
            totalName += expand;
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
            totalName += "%C" + QString::number(stepValue.size()) + "%";
            stepValue.push_back(1);
        }
    }
    }
}

void Mask::maskN(QString mask)
{
    try {
        if (mask.endsWith('-')) {
            QString totalNumber;
            for (int i = 0; i < mask.size() - 1; i++) {
                if (mask.at(i).isNumber())
                    totalNumber += mask.at(i);
                else
                    throw 1;
            }
            int Index = totalNumber.toInt() - 1;
            if (Index > name.size())
                throw 2;
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
                    throw 1;
            }
            int diff = totalNumber.toInt() + 1;
            if (diff - 1 > name.size())
                throw 2;
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
                        throw 1;
                    if (mask.at(++i) == '-') {
                        i++;
                        choise = 1;
                    } else {
                        throw 1;
                    }
                } else
                    throw 1;
            }
            if (number[0].isEmpty() || number[1].isEmpty()) {
                throw 1;
            }
            int first = number[0].toInt() - 1;
            int second = number[1].toInt();
            if (first > name.size() || second > name.size())
                throw 2;
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
                        throw 1;
                    choise = 1;
                } else
                    throw 1;
            }
            if (number[0].isEmpty() || number[1].isEmpty()) {
                throw 1;
            }

            int first = number[0].toInt() - 1;
            int second = number[1].toInt() - 1;
            if (first > second || second >= name.size())
                throw 2;
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
                        throw 1;
                    choise = 1;
                } else {
                    throw 1;
                }
            }
            if (number[0].isEmpty() || number[1].isEmpty()) {
                throw 1;
            }

            int first = number[0].toInt() - 1;
            int second = number[1].toInt() + first;

            if (first > name.size() || second > name.size()) {
                throw 2;
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
                    throw 1;
                }
            }
            int index = number.toInt() - 1;
            if (index > name.size())
                throw 2;
            totalName += name.at(index);
        }
    } catch (int a) {
    }
}

void Mask::maskE(QString mask)
{
    try {
        if (!mask.contains('-')) {
            throw 1;
        } else {
            QString number[2];
            int choise = 0;
            for (int i = 0; i < mask.size(); i++) {
                QChar c = mask.at(i);
                if (c.isNumber()) {
                    number[choise] += c;
                } else if (c == '-') {
                    if (choise == 1)
                        throw 1;
                    choise = 1;
                } else
                    throw 1;
            }
            int begin = number[0].toInt() - 1;
            int end = number[1].toInt() - 1;
            if (end < begin || begin > expand.size() || end >= expand.size())
                throw 2;
            for (int i = begin; i <= end; i++) {
                totalName += expand.at(i);
            }
        }
    } catch (int a) {
    }
}

void Mask::maskYMD(QString mask)
{
    try {
        if (!mask.endsWith('Y') && !mask.endsWith('M') && !mask.endsWith('D'))
            throw 1;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c == 'Y') {
                totalName += '%' + c + '%';
            } else if (c == 'M') {
                totalName += '%' + c + '%';
            } else if (c == 'D') {
                totalName += '%' + c + '%';
            } else {
                totalName += c;
            }
        }
    } catch (int a) {
    }
}

void Mask::maskHMS(QString mask)
{
    try {
        if (!mask.endsWith('h') && !mask.endsWith('s') && !mask.endsWith('m'))
            throw 1;
        for (int i = 0; i < mask.size(); i++) {
            QChar c = mask.at(i);
            if (c == 'h') {
                totalName += '%' + c + '%';
            } else if (c == 's') {
                totalName += '%' + c + '%';
            } else if (c == 'm') {
                totalName += '%' + c + '%';
            } else {
                totalName += c;
            }
        }
    } catch (int a) {
    }
}

void Mask::maskC(QString mask)
{
}

QString Mask::getTotalName() const
{
    return totalName;
}
