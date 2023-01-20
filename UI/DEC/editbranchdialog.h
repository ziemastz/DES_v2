#ifndef EDITBRANCHDIALOG_H
#define EDITBRANCHDIALOG_H

#include <QDialog>

namespace Ui {
class EditBranchDialog;
}

class EditBranchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditBranchDialog(QWidget *parent = nullptr);
    ~EditBranchDialog();

private:
    Ui::EditBranchDialog *ui;
};

#endif // EDITBRANCHDIALOG_H
