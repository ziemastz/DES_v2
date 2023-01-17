#include "recordensdf.h"

RecordENSDF::RecordENSDF()
{
}

RecordENSDF &RecordENSDF::operator =(const QString &str)
{
    this->_str = str;
    return *this;
}

int RecordENSDF::size() const
{
    return _str.size();
}

int RecordENSDF::count(const QRegExp &regExp) const
{
    return _str.count(regExp);
}

int RecordENSDF::count(const QString &str) const
{
    return _str.count(str);
}

int RecordENSDF::count(const QChar &sign) const
{
    return _str.count(sign);
}

QChar RecordENSDF::at(const int &index) const
{
    return _str.at(index-1);
}

QString RecordENSDF::mid(const int &begin, const int &end) const
{
    return _str.mid(begin-1,end-begin+1);
}
