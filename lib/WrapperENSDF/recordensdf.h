#ifndef RECORDENSDF_H
#define RECORDENSDF_H

#include <QString>

class RecordENSDF
{
public:
    RecordENSDF();
    RecordENSDF operator=(const QString &);
    int size() const;
    int count(const QRegExp &regExp) const;
    int count(const QString &str) const;
    int count(const QChar &sign) const;
    QChar at(const int &index) const;
    /**
     * @brief mid cut the string in range column begin and end
     * @param begin column
     * @param end column
     * @return selected range of column
     */
    QString mid(const int &begin, const int &end) const;

private:
    QString _str;
};

#endif // RECORDENSDF_H
