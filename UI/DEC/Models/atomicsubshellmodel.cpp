#include "atomicsubshellmodel.h"



QStringList AtomicSubshellModel::getSubshells() const
{
    return subshells;
}

QStringList AtomicSubshellModel::getSubshells(const QString &fromSubshell) const
{
    QStringList ret;
    int index = subshells.indexOf(fromSubshell);
    for(int i=index+1; i<subshells.size(); i++) {
        ret << subshells.at(i);
    }
    return ret;
}
