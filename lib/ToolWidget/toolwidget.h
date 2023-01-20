#ifndef PRIME_TOOLWIDGET_H
#define PRIME_TOOLWIDGET_H
#include <QObject>
#include <QStringList>
#include <QTableWidget>
#include <QLineEdit>

class ToolWidget
{
public:
    //tableWidget
    static void clearTableWidget(QTableWidget *table);
    static void addRecord(QTableWidget *table, const QStringList& record);
    static void addTable(QTableWidget *table, const QVector<QStringList>& data);

    //lineedit
    static void integerNumberModeLineEdit(const QString &arg, QLineEdit *lineEdit);
    static void realNumberModeLineEdit(const QString &arg, QLineEdit *lineEdit);
};

#endif // PRIME_TOOLWIDGET_H
