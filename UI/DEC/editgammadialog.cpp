#include "editgammadialog.h"
#include "ui_editgammadialog.h"
#include "toolwidget.h"

EditGammaDialog::EditGammaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGammaDialog)
{
    ui->setupUi(this);

    connect(ui->energy_g_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->total_internal_conversion_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->intensity_g_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(percentageNumberLineEdit(QString)));
    connect(ui->intensity_cc_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(percentageNumberLineEdit(QString)));
}

EditGammaDialog::~EditGammaDialog()
{
    delete ui;
}

void EditGammaDialog::load(GammaModel *gamma)
{
    _gamma = *gamma;

    ui->nuclide_lineEdit->setText(_gamma.nuclide);
    ui->initial_level_lineEdit->setText(QString::number(_gamma.initialLevel_keV));
    ui->final_level_lineEdit->setText(QString::number(_gamma.finalLevel_keV));

    ui->energy_g_lineEdit->setText(QString::number(_gamma.energy));
    ui->intensity_g_lineEdit->setText(QString::number(_gamma.intensity));
    ui->total_internal_conversion_lineEdit->setText(QString::number(_gamma.total_internal_conversion));
    ui->multipolarity_lineEdit->setText(_gamma.multipolarity);

    updateSubshellCCTable();

}

void EditGammaDialog::on_cancel_pushButton_clicked()
{
    close();
}

void EditGammaDialog::updateSubshellCCTable()
{
    ToolWidget::clearTableWidget(ui->subshell_cc_tableWidget);
    QStringList keys = _gamma.conversion_electrons.keys();
    std::sort(keys.begin(), keys.end());

    for(int i=0;i<keys.size();i++) {
        QStringList row;
        row << keys.at(i)
            << QString::number(_gamma.conversion_electrons.value(keys.at(i)));
        ToolWidget::addRecord(ui->subshell_cc_tableWidget,row);
    }
}


void EditGammaDialog::on_addUpdate_subshell_pushButton_clicked()
{
    QString subshell = ui->subshell_cc_comboBox->currentText();
    QString intensity = ui->intensity_cc_lineEdit->text();
    if(subshell.isEmpty() || intensity.isEmpty())
        return;

    if(intensity.toDouble() == 0.0) {
        _gamma.conversion_electrons.remove(subshell);

    }else if(_gamma.conversion_electrons.contains(subshell)) {
        _gamma.conversion_electrons[subshell] = intensity.toDouble();
    }else{
        _gamma.conversion_electrons.insert(subshell,intensity.toDouble());
    }
    updateSubshellCCTable();
}

GammaModel EditGammaDialog::gamma() const
{
    return _gamma;
}

void EditGammaDialog::urealNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }
}

void EditGammaDialog::percentageNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }else if(line->text().toDouble() > 100) {
        line->setText("100");
    }
}

void EditGammaDialog::on_update_pushButton_clicked()
{
    accept();
}

void EditGammaDialog::on_energy_g_lineEdit_editingFinished()
{
    _gamma.energy = ui->energy_g_lineEdit->text().toDouble();
}

void EditGammaDialog::on_intensity_g_lineEdit_editingFinished()
{
    _gamma.intensity = ui->intensity_g_lineEdit->text().toDouble();
}

void EditGammaDialog::on_total_internal_conversion_lineEdit_editingFinished()
{
    _gamma.total_internal_conversion = ui->total_internal_conversion_lineEdit->text().toDouble();
}

void EditGammaDialog::on_multipolarity_lineEdit_editingFinished()
{
    _gamma.multipolarity = ui->multipolarity_lineEdit->text();
}

