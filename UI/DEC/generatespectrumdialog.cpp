#include "generatespectrumdialog.h"
#include "ui_generatespectrumdialog.h"

GenerateSpectrumDialog::GenerateSpectrumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateSpectrumDialog)
{
    ui->setupUi(this);
}

GenerateSpectrumDialog::~GenerateSpectrumDialog()
{
    delete ui;
}
