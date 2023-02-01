#include "atomicdatadialog.h"
#include "ui_atomicdatadialog.h"
#include "atomicsubshelldialog.h"
#include <QPushButton>
#include "Controllers/atomicdatacontroller.h"

AtomicDataDialog::AtomicDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AtomicDataDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_K, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);

    connect(ui->pushButton_L1, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_L2, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_L3, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);

    connect(ui->pushButton_M1, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_M2, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_M3, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_M4, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_M5, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);

    connect(ui->pushButton_N1, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_N2, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_N3, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_N4, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_N5, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_N6, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_N7, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);

    connect(ui->pushButton_O1, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_O2, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_O3, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_O4, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_O5, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_O6, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_O7, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);

    connect(ui->pushButton_P1, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_P2, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_P3, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_P4, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
    connect(ui->pushButton_P5, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);

    connect(ui->pushButton_Q1, &QPushButton::clicked, this, &AtomicDataDialog::openSubshell);
}

AtomicDataDialog::~AtomicDataDialog()
{
    delete ui;
}

void AtomicDataDialog::setNuclide(const QString &symbol)
{
    _symbol = symbol;
    ui->groupBox->setTitle(symbol);
    ui->label_titleApp->setText("Atomic Data of "+symbol);

    loadData();
}

void AtomicDataDialog::openSubshell()
{
    QPushButton *pushButton = (QPushButton*)sender();
    AtomicSubshellDialog *subshell;

    subshell = new AtomicSubshellDialog(_symbol,pushButton->text(),this);
    subshell->show();
}

void AtomicDataDialog::loadData()
{
    AtomicDataController atomicContr;
    data = atomicContr.getAtomicData(_symbol);
}

void AtomicDataDialog::on_cancel_pushButton_clicked()
{
    close();
}


void AtomicDataDialog::on_save_pushButton_clicked()
{

}

