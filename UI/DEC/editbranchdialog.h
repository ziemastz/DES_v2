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

private:
    Ui::EditBranchDialog *ui;
    BranchModel _branch;

    void ReloadECSubshellPropabilityTable();
};

#endif // EDITBRANCHDIALOG_H
