#include "toolwidget.h"

void ToolWidget::clearTableWidget(QTableWidget *table)
{
    int rows = table->rowCount();
    for(int i=0;i<rows;i++)
        table->removeRow(0);
}

void ToolWidget::addRecord(QTableWidget *table, const QStringList &record)
{
    if(record.count() > table->columnCount())
        return;
    int rows = table->rowCount();
    int columns = record.count();
    table->insertRow(rows);
    table->blockSignals(true);
    for(int j=0;j<columns;j++) {
        QTableWidgetItem * item = new QTableWidgetItem(record.at(j));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(rows,j,item);
    }
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->blockSignals(false);
}

void ToolWidget::addTable(QTableWidget *table, const QVector<QStringList> &data)
{
    foreach(QStringList record, data)
        addRecord(table,record);
}

void ToolWidget::integerNumberModeLineEdit(const QString &arg, QLineEdit *lineEdit)
{
    QString text = QString(arg).replace(",",".");
    int curPos = lineEdit->cursorPosition();
    bool ok;
    text.toInt(&ok);
    if(!ok) {
        lineEdit->setText(lineEdit->text().remove(curPos-1,1));
        lineEdit->setCursorPosition(curPos-1);
    }else {
        lineEdit->setText(text);
        lineEdit->setCursorPosition(curPos);
    }
}

void ToolWidget::realNumberModeLineEdit(const QString &arg, QLineEdit *lineEdit)
{
    QString text = QString(arg).replace(",",".");
    int curPos = lineEdit->cursorPosition();
    bool ok;
    text.toDouble(&ok);
    if(!ok) {
        lineEdit->setText(lineEdit->text().remove(curPos-1,1));
        lineEdit->setCursorPosition(curPos-1);
    }else {
        lineEdit->setText(text);
        lineEdit->setCursorPosition(curPos);
    }
}
