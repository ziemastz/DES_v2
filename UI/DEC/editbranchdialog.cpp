#include "editbranchdialog.h"
#include "ui_editbranchdialog.h"

EditBranchDialog::EditBranchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBranchDialog)
{
    ui->setupUi(this);
}

EditBranchDialog::~EditBranchDialog()
{
    delete ui;
}
