#ifndef ATOMICDATADIALOG_H
#define ATOMICDATADIALOG_H

#include <QDialog>

namespace Ui {
class AtomicDataDialog;
}

class AtomicDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AtomicDataDialog(QWidget *parent = nullptr);
    ~AtomicDataDialog();
    void setNuclide(const QString &symbol);
private slots:
    void openSubshell();
private:
    Ui::AtomicDataDialog *ui;
    QString _symbol;
};

#endif // ATOMICDATADIALOG_H
