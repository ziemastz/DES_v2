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

void EditBranchDialog::load(BranchModel *branch)
{
    //parent
    ui->parent_label->setText(branch->parent.symbol);
    ui->parent_half_life_value_lineEdit->setText(branch->parent.halfLifeValue);
    ui->parent_half_life_uncertainty_lineEdit->setText(branch->parent.halfLifeUncertainty);
    ui->parent_half_life_unit_comboBox->setCurrentIndex(ui->parent_half_life_unit_comboBox->findText(branch->parent.halfLifeUnit));

    //daughter
    ui->daughter_label->setText(branch->daughter.symbol);
    ui->daughter_half_life_value_lineEdit->setText(branch->daughter.halfLifeValue);
    ui->daughter_half_life_uncertainty_lineEdit->setText(branch->daughter.halfLifeUncertainty);
    ui->daughter_half_life_unit_comboBox->setCurrentIndex(ui->parent_half_life_unit_comboBox->findText(branch->daughter.halfLifeUnit));

    //transition
    ui->transition_lineEdit->setText(branch->transition);
    ui->total_intensity_lineEdit->setText(branch->intensity);
    ui->excited_level_lineEdit->setText(branch->level.excited_level_keV);
    ui->level_half_life_value_lineEdit->setText(branch->level.halfLifeValue);
    ui->level_half_life_uncertainty_lineEdit->setText(branch->level.halfLifeUncertainty);
    ui->level_half_life_unit_comboBox->setCurrentIndex(ui->parent_half_life_unit_comboBox->findText(branch->level.halfLifeUnit));

    //transition type
    if(branch->transition == "BETA-") {

    }
    if(branch->transition == "ALPHA") {

    }
    if(branch->transition == "EC") {

    }
}
