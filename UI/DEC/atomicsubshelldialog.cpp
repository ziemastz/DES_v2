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
    ui->label_vacancy->setText(subshell);
    ui->label_vacancy_x->setText(subshell);

    ui->comboBox_occupancy->addItems(data.getSubshells(subshell));
    ui->comboBox_occupancy_x->addItems(data.getSubshells(subshell));
}

AtomicSubshellDialog::~AtomicSubshellDialog()
{
    delete ui;
}

void AtomicSubshellDialog::on_comboBox_occupancy_currentTextChanged(const QString &arg1)
{
    QString current_emitting = ui->comboBox_emitting->currentText();

    ui->comboBox_emitting->clear();
    ui->comboBox_emitting->addItem(arg1);
    ui->comboBox_emitting->addItems(data.getSubshells(arg1));
    ui->comboBox_emitting->setCurrentIndex(ui->comboBox_emitting->findText(current_emitting));
}

