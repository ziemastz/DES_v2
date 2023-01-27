#ifndef EDITGAMMADIALOG_H
#define EDITGAMMADIALOG_H

#include <QDialog>
#include "Models/gammamodel.h"

namespace Ui {
class EditGammaDialog;
}

class EditGammaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditGammaDialog(QWidget *parent = nullptr);
    ~EditGammaDialog();
    void load(GammaModel *gamma);

    GammaModel gamma() const;

private slots:
    void on_cancel_pushButton_clicked();

    void on_addUpdate_subshell_pushButton_clicked();

    void on_update_pushButton_clicked();

    void on_energy_g_lineEdit_editingFinished();

    void on_intensity_g_lineEdit_editingFinished();

    void on_total_internal_conversion_lineEdit_editingFinished();

    void on_multipolarity_lineEdit_editingFinished();

    void on_energy_g_lineEdit_textChanged(const QString &arg1);

    void on_intensity_g_lineEdit_textChanged(const QString &arg1);

    void on_total_internal_conversion_lineEdit_textChanged(const QString &arg1);

private:
    Ui::EditGammaDialog *ui;
    GammaModel _gamma;

    void updateSubshellCCTable();
};

#endif // EDITGAMMADIALOG_H
