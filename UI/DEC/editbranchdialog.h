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
    void realNumberLineEdit(const QString &arg1);
    void percentageNumberLineEdit(const QString &arg1);
    void on_alpha_energy_lineEdit_editingFinished();

    void on_beta_endpoint_energy_lineEdit_editingFinished();

    void on_forbiddenness_comboBox_currentTextChanged(const QString &arg1);

    void on_coeff_a_lineEdit_editingFinished();

    void on_coeff_b_lineEdit_editingFinished();

    void on_coeff_c_lineEdit_editingFinished();

    void on_coeff_d_lineEdit_editingFinished();

    void on_coeff_e_lineEdit_editingFinished();

    void on_expShapeFactor_comboBox_currentTextChanged(const QString &arg1);

    void on_exp_a_lineEdit_editingFinished();

    void on_exp_b_lineEdit_editingFinished();

    void on_exp_c_lineEdit_editingFinished();

    void on_exp_d_lineEdit_editingFinished();

    void on_mixing_ratio_lineEdit_editingFinished();

private:
    Ui::EditBranchDialog *ui;
    BranchModel _branch;

    void ReloadECSubshellPropabilityTable();
};

#endif // EDITBRANCHDIALOG_H
