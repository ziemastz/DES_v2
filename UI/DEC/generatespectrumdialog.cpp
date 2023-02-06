#include "generatespectrumdialog.h"
#include "ui_generatespectrumdialog.h"
#include "toolwidget.h"

GenerateSpectrumDialog::GenerateSpectrumDialog(const DecaySchemeModel &radionuclideDecay, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateSpectrumDialog),
    decay(radionuclideDecay)
{
    ui->setupUi(this);

    connect(ui->resolvingTime_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->deadTime_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->decayEvents_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(uintegerNumberLineEdit(QString)));

}

GenerateSpectrumDialog::~GenerateSpectrumDialog()
{
    delete ui;
}

void GenerateSpectrumDialog::on_cancel_pushButton_clicked()
{
    close();
}


void GenerateSpectrumDialog::on_start_pushButton_clicked()
{

}

void GenerateSpectrumDialog::uintegerNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::integerNumberModeLineEdit(arg1,line);
    if(line->text().toInt() < 0) {
        line->setText("0");
    }
}

void GenerateSpectrumDialog::urealNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }
}

