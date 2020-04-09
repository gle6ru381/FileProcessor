#include "mask.h"

Mask::Mask(QString name, QString expand, QString mask)
    : name(name), expand(expand), fullMask(mask)
{
}

void Mask::readName()
{
    for (int i = 0; i < fullMask.size(); i++) {
        if (fullMask.at(i) == '[') {
            QString mask;
            while (fullMask.at(++i) != ']') {
                mask += name.at(i);
            }
            readMask(mask);
            i++;
        } else {
            totalName += fullMask.at(i);
        }
    }
}

void Mask::readMask(QString mask)
{
    switch (mask.at(0).unicode()) {
    case 'N': {
        maskN(mask.remove(0, 1));
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
            int Index = totalNumber.toInt();
            if (Index > name.size())
                throw 2;
            while (Index++ < name.size()) {
                totalName += name.at(Index);
            }
        } else if (mask.at(0) == '-') {
            QString totalNumber;
            for (int i = 1; i < mask.size(); i++) {
                if (mask.at(i).isNumber())
                    totalNumber += mask.at(i);
                else
                    throw 1;
            }
        }
    } catch (int a) {
    }
}
