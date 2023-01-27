#ifndef EDITBRANCHDIALOG_H
#define EDITBRANCHDIALOG_H

#include <QDialog>
#include "Models/branchmodel.h"

namespace Ui {
class EditBranchDialog;
}

class EditBranchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditBranchDialog(QWidget *parent = nullptr);
    ~EditBranchDialog();
    void load(BranchModel *branch);

    BranchModel branch() const;

private slots:
    void on_addUpdate_subshell_pushButton_clicked();

    void on_cancel_pushButton_clicked();

    void on_save_pushButton_clicked();

    void on_atomic_data_pushButton_clicked();

    void on_parent_half_life_value_lineEdit_editingFinished();

    void on_parent_half_life_uncertainty_lineEdit_editingFinished();

    void on_parent_half_life_unit_comboBox_currentTextChanged(const QString &arg1);

    void on_total_intensity_lineEdit_editingFinished();

    void on_level_half_life_value_lineEdit_editingFinished();

    void on_level_half_life_uncertainty_lineEdit_editingFinished();

    void on_level_half_life_unit_comboBox_currentTextChanged(const QString &arg1);

    void on_daughter_half_life_value_lineEdit_editingFinished();

    void on_daughter_half_life_uncertainty_lineEdit_editingFinished();

    void on_daughter_half_life_unit_comboBox_currentTextChanged(const QString &arg1);

    void urealNumberLineEdit(const QString &arg1);
    void percentageNumberLineEdit(const QString &arg1);
private:
    Ui::EditBranchDialog *ui;
    BranchModel _branch;

    void ReloadECSubshellPropabilityTable();
};

#endif // EDITBRANCHDIALOG_H
