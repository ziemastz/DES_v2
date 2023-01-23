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

private:
    Ui::EditBranchDialog *ui;
};

#endif // EDITBRANCHDIALOG_H
