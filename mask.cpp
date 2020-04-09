#include "mask.h"

Mask::Mask(QString name, QString expand, QString mask)
    : name(name), expand(expand), mask(mask)
{
}

void Mask::readName()
{
    for (int i = 0; i < name.size(); i++) {
        if (name.at(i) == '[') {
            QString mask;
            while (name.at(++i) != ']') {
                mask += name.at(i);
            }
            readMask(mask);
            i++;
        } else {
            totalName += name.at(i);
        }
    }
}

void Mask::readMask(QString mask)
{
}
