#ifndef ATOMICSUBSHELLDIALOG_H
#define ATOMICSUBSHELLDIALOG_H

#include <QDialog>
#include "Models/atomicsubshellmodel.h"

namespace Ui {
class AtomicSubshellDialog;
}

class AtomicSubshellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AtomicSubshellDialog(const QString &symbol, const QString &subshell, QWidget *parent = nullptr);
    ~AtomicSubshellDialog();

private:
    Ui::AtomicSubshellDialog *ui;
    QString _symbol;
    QString _subshell;

    AtomicSubshellModel data;
};

#endif // ATOMICSUBSHELLDIALOG_H
