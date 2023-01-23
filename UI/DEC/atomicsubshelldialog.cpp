#include "atomicsubshelldialog.h"
#include "ui_atomicsubshelldialog.h"

AtomicSubshellDialog::AtomicSubshellDialog(const QString &symbol, const QString &subshell, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AtomicSubshellDialog),
    _symbol(symbol),
    _subshell(subshell)
{
    ui->setupUi(this);
    ui->groupBox_main->setTitle(subshell + " - Subshell");
    ui->label_titleApp->setText("Atomic Subshell "+subshell+" of "+symbol);
}

AtomicSubshellDialog::~AtomicSubshellDialog()
{
    delete ui;
}