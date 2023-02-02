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
    void load(const AtomicSubshellModel &loadData);
    AtomicSubshellModel getData() const;

private slots:
    void on_comboBox_occupancy_currentTextChanged(const QString &arg1);

    void on_pushButton_addAugerTransition_clicked();

    void on_pushButton_addXRayTransition_clicked();

    void on_cancel_pushButton_clicked();

    void on_save_pushButton_clicked();

    void urealNumberLineEdit(const QString &arg1);
    void uintegerNumberLineEdit(const QString &arg1);
    void percentageNumberLineEdit(const QString &arg1);
    void on_lineEdit_energy_editingFinished();

    void on_lineEdit_electrons_editingFinished();

private:
    Ui::AtomicSubshellDialog *ui;
    QString _symbol;
    QString _subshell;

    AtomicSubshellModel data;
    void reloadAugerTable();
    void reloadXRayTable();
};

#endif // ATOMICSUBSHELLDIALOG_H
