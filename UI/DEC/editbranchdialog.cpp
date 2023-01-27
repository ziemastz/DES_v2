#include "editbranchdialog.h"
#include "ui_editbranchdialog.h"
#include "toolwidget.h"
#include "atomicdatadialog.h"
#include "Controllers/nuclidecontroller.h"
#include "Controllers/branchcontroller.h"
EditBranchDialog::EditBranchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBranchDialog)
{
    ui->setupUi(this);
    NuclideController nuc_contr;
    QStringList unit_hl = nuc_contr.getStandardFormatHalfLifeUnits();
    ui->parent_half_life_unit_comboBox->addItems(unit_hl);
    ui->level_half_life_unit_comboBox->addItems(unit_hl);
    ui->daughter_half_life_unit_comboBox->addItems(unit_hl);

    BranchController branchContr;
    ui->forbiddenness_comboBox->addItems(branchContr.forbiddenness());
    ui->expShapeFactor_comboBox->addItems(branchContr.expShapeFactors());


    connect(ui->parent_half_life_value_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->parent_half_life_uncertainty_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->daughter_half_life_value_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->daughter_half_life_uncertainty_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->level_half_life_value_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->level_half_life_uncertainty_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->total_intensity_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(percentageNumberLineEdit(QString)));

    connect(ui->alpha_energy_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));

    connect(ui->beta_endpoint_energy_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->coeff_a_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));
    connect(ui->coeff_b_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));
    connect(ui->coeff_c_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));
    connect(ui->coeff_d_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));
    connect(ui->coeff_e_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));

    connect(ui->exp_a_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));
    connect(ui->exp_b_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));
    connect(ui->exp_c_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));
    connect(ui->exp_d_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(realNumberLineEdit(QString)));

    connect(ui->mixing_ratio_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
}

EditBranchDialog::~EditBranchDialog()
{
    delete ui;
}

void EditBranchDialog::load(BranchModel *branch)
{
    _branch = *branch;
    //parent
    ui->parent_label->setText(branch->parent.symbol);
    ui->parent_half_life_value_lineEdit->setText(QString::number(branch->parent.halfLifeValue));
    ui->parent_half_life_uncertainty_lineEdit->setText(QString::number(branch->parent.halfLifeUncery));
    ui->parent_half_life_unit_comboBox->setCurrentIndex(ui->parent_half_life_unit_comboBox->findText(branch->parent.halfLifeUnit));

    //daughter
    ui->daughter_label->setText(branch->daughter.symbol);
    ui->daughter_half_life_value_lineEdit->setText(QString::number(branch->daughter.halfLifeValue));
    ui->daughter_half_life_uncertainty_lineEdit->setText(QString::number(branch->daughter.halfLifeUncery));
    ui->daughter_half_life_unit_comboBox->setCurrentIndex(ui->parent_half_life_unit_comboBox->findText(branch->daughter.halfLifeUnit));

    //transition
    ui->transition_lineEdit->setText(branch->transition);
    ui->total_intensity_lineEdit->setText(QString::number(branch->intensity));
    ui->excited_level_lineEdit->setText(QString::number(branch->level.excited_level_keV));
    ui->level_half_life_value_lineEdit->setText(QString::number(branch->level.halfLifeValue));
    ui->level_half_life_uncertainty_lineEdit->setText(QString::number(branch->level.halfLifeUncertainty));
    ui->level_half_life_unit_comboBox->setCurrentIndex(ui->parent_half_life_unit_comboBox->findText(branch->level.halfLifeUnit));

    //transition type
    if(branch->transition == "ALPHA") {
        ui->stackedWidget->setCurrentIndex(0);
        ui->alpha_energy_lineEdit->setText(branch->alpha_energy_kev);
    }
    if(branch->transition == "BETA-") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    if(branch->transition == "EC") {
        ui->stackedWidget->setCurrentIndex(2);
        ui->intensity_beta_plus_lineEdit->setText(QString::number(branch->ec.intensityBetaPlus));
        ui->intensity_ec_lineEdit->setText(QString::number(branch->ec.intensityEC));
        ReloadECSubshellPropabilityTable();
    }
}

void EditBranchDialog::on_addUpdate_subshell_pushButton_clicked()
{
    QString subshell = ui->subshell_ec_comboBox->currentText();
    QString intensity = ui->subshell_intensity_ec_lineEdit->text();
    if(subshell.isEmpty() || intensity.isEmpty())
        return;

    if(intensity.toDouble() == 0.0) {
        _branch.ec.subshell_probability.remove(subshell);

    }else if(_branch.ec.subshell_probability.contains(subshell)) {
        _branch.ec.subshell_probability[subshell] = intensity.toDouble();
    }else{
        _branch.ec.subshell_probability.insert(subshell,intensity.toDouble());
    }

    ReloadECSubshellPropabilityTable();
}

BranchModel EditBranchDialog::branch() const
{
    return _branch;
}

void EditBranchDialog::ReloadECSubshellPropabilityTable()
{
    ToolWidget::clearTableWidget(ui->subshell_ec_tableWidget);
    QStringList keys = _branch.ec.subshell_probability.keys();
    std::sort(keys.begin(), keys.end());

    for(int i=0;i<keys.size();i++) {
        QStringList row;
        row << keys.at(i)
            << QString::number(_branch.ec.subshell_probability.value(keys.at(i)));
        ToolWidget::addRecord(ui->subshell_ec_tableWidget,row);
    }
}


void EditBranchDialog::on_cancel_pushButton_clicked()
{
    close();
}


void EditBranchDialog::on_save_pushButton_clicked()
{
    accept();
}


void EditBranchDialog::on_atomic_data_pushButton_clicked()
{
    AtomicDataDialog atomicData;
    atomicData.setNuclide(ui->daughter_label->text());
    atomicData.exec();
}


void EditBranchDialog::on_parent_half_life_value_lineEdit_editingFinished()
{
    _branch.parent.halfLifeValue = ui->parent_half_life_value_lineEdit->text().toDouble();
}


void EditBranchDialog::on_parent_half_life_uncertainty_lineEdit_editingFinished()
{
    _branch.parent.halfLifeUncery = ui->parent_half_life_uncertainty_lineEdit->text().toDouble();
}


void EditBranchDialog::on_parent_half_life_unit_comboBox_currentTextChanged(const QString &arg1)
{
    _branch.parent.halfLifeUnit = arg1;
}


void EditBranchDialog::on_total_intensity_lineEdit_editingFinished()
{
    _branch.intensity = ui->total_intensity_lineEdit->text().toDouble();
}


void EditBranchDialog::on_level_half_life_value_lineEdit_editingFinished()
{
    _branch.level.halfLifeValue = ui->level_half_life_value_lineEdit->text().toDouble();
}


void EditBranchDialog::on_level_half_life_uncertainty_lineEdit_editingFinished()
{
    _branch.level.halfLifeUncertainty = ui->level_half_life_uncertainty_lineEdit->text().toDouble();
}


void EditBranchDialog::on_level_half_life_unit_comboBox_currentTextChanged(const QString &arg1)
{
    _branch.level.halfLifeUnit = arg1;
}


void EditBranchDialog::on_daughter_half_life_value_lineEdit_editingFinished()
{
    _branch.daughter.halfLifeValue = ui->daughter_half_life_value_lineEdit->text().toDouble();
}


void EditBranchDialog::on_daughter_half_life_uncertainty_lineEdit_editingFinished()
{
    _branch.daughter.halfLifeUncery = ui->daughter_half_life_uncertainty_lineEdit->text().toDouble();
}


void EditBranchDialog::on_daughter_half_life_unit_comboBox_currentTextChanged(const QString &arg1)
{
    _branch.daughter.halfLifeUnit = arg1;
}

void EditBranchDialog::urealNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }
}

void EditBranchDialog::realNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
}

void EditBranchDialog::percentageNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }else if(line->text().toDouble() > 100) {
        line->setText("100");
    }
}


void EditBranchDialog::on_alpha_energy_lineEdit_editingFinished()
{
    _branch.alpha_energy_kev = ui->alpha_energy_lineEdit->text().toDouble();
}


void EditBranchDialog::on_beta_endpoint_energy_lineEdit_editingFinished()
{
    _branch.beta.endpoint_energy_keV = ui->beta_endpoint_energy_lineEdit->text().toDouble();
}


void EditBranchDialog::on_forbiddenness_comboBox_currentTextChanged(const QString &arg1)
{
    _branch.beta.forbiddenness = arg1;
}


void EditBranchDialog::on_coeff_a_lineEdit_editingFinished()
{
    _branch.beta.coeff_a = ui->coeff_a_lineEdit->text().toDouble();
}


void EditBranchDialog::on_coeff_b_lineEdit_editingFinished()
{
    _branch.beta.coeff_b = ui->coeff_b_lineEdit->text().toDouble();
}


void EditBranchDialog::on_coeff_c_lineEdit_editingFinished()
{
    _branch.beta.coeff_c = ui->coeff_c_lineEdit->text().toDouble();
}


void EditBranchDialog::on_coeff_d_lineEdit_editingFinished()
{
    _branch.beta.coeff_d = ui->coeff_d_lineEdit->text().toDouble();
}


void EditBranchDialog::on_coeff_e_lineEdit_editingFinished()
{
    _branch.beta.coeff_e = ui->coeff_e_lineEdit->text().toDouble();
}


void EditBranchDialog::on_expShapeFactor_comboBox_currentTextChanged(const QString &arg1)
{
    _branch.beta.exp_shape_factor = arg1;
}


void EditBranchDialog::on_exp_a_lineEdit_editingFinished()
{
    _branch.beta.exp_coeff_a = ui->exp_a_lineEdit->text().toDouble();
}


void EditBranchDialog::on_exp_b_lineEdit_editingFinished()
{
    _branch.beta.exp_coeff_b = ui->exp_b_lineEdit->text().toDouble();
}


void EditBranchDialog::on_exp_c_lineEdit_editingFinished()
{
    _branch.beta.exp_coeff_c = ui->exp_c_lineEdit->text().toDouble();
}


void EditBranchDialog::on_exp_d_lineEdit_editingFinished()
{
    _branch.beta.exp_coeff_d = ui->exp_d_lineEdit->text().toDouble();
}


void EditBranchDialog::on_mixing_ratio_lineEdit_editingFinished()
{
    _branch.beta.mixing_ratio = ui->mixing_ratio_lineEdit->text().toDouble();
}

