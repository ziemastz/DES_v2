#ifndef ATOMICDATADIALOG_H
#define ATOMICDATADIALOG_H

#include <QDialog>
#include "Controllers/atomicdatacontroller.h"

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
    void on_cancel_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_radius_lineEdit_editingFinished();

    void on_lineEdit_f12_editingFinished();

    void on_lineEdit_f13_editingFinished();

    void on_lineEdit_f23_editingFinished();

    void on_addUpdate_subshell_pushButton_clicked();

    void urealNumberLineEdit(const QString &arg1);

    void percentageNumberLineEdit(const QString &arg1);
private:
    Ui::AtomicDataDialog *ui;
    QString _symbol;

    AtomicDataModel data;

    void reloadFluorescenceTable();
    void loadData();
};

#endif // ATOMICDATADIALOG_H
