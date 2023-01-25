#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include "wrapperensdf.h"
#include <QFileDialog>
#include "toolwidget.h"
#include "editbranchdialog.h"

#include "Controllers/nuclidecontroller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_versionApp->setText(QApplication::applicationVersion());
    ui->label_currentDate->setText(QDateTime::currentDateTime().toString("dddd, d MMMM yyyy"));

    NuclideController nuclide;
    ui->selected_radionuclide_comboBox->addItems(nuclide.getNuclides());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_import_ensdf_pushButton_clicked()
{
    QString selected_file = QFileDialog::getOpenFileName(this,tr("Select ENSDF"),QDir::homePath());

    if(selected_file.isEmpty()) {
        qDebug() << "No select file ENSDF";
        return;
    }

    // wrapper data
    WrapperENSDF ensdf(selected_file);

    if(!ensdf.read()) {
        qDebug() << "Failed to load data from ENSDF";
        return;
    }

    //load data to decay model
    decay.radionuclide = ensdf.getParent();
    decay.branches.clear();
    int noDaughters = ensdf.countDaughters();
    for(int i = 0; i < noDaughters; i++) {
        int noLevels = ensdf.countLevels(i);
        for(int j = 0; j < noLevels; j++) {
            decay.branches << BranchModel();
            //level & daughter
            decay.branches.last().level.excited_level_keV = ensdf.getLevelEnergy(i,j);
            decay.branches.last().level.halfLifeValue = ensdf.getHalfLifeValueLevel(i,j);
            decay.branches.last().level.halfLifeUncertainty = ensdf.getHalfLifeUncertaintyLevel(i,j);
            decay.branches.last().level.halfLifeUnit = ensdf.getHalfLifeUnitLevel(i,j);

            decay.branches.last().daughter.a = ensdf.getA_Daughter(i).toInt();
            decay.branches.last().daughter.z = ensdf.getZ_Daughter(i);
            decay.branches.last().daughter.symbol = ensdf.getDaughter(i);
            decay.branches.last().daughter.halfLifeValue = ensdf.getHalfLifeValueDaughter(i).toDouble();
            decay.branches.last().daughter.halfLifeUncery = ensdf.getHalfLifeUncertaintyDaughter(i).toDouble();
            decay.branches.last().daughter.halfLifeUnit = ensdf.getHalfLifeUnitDaughter(i);
            decay.branches.last().daughter.spinParity = ensdf.getSpinParityDaughter(i);

            if(ensdf.findBeta(i,j)) {
                decay.branches.last().parent.a = ensdf.getA_Parent(i).toInt();
                decay.branches.last().parent.z = ensdf.getZ_Parent(i);
                decay.branches.last().parent.symbol = ensdf.getParent(i);
                decay.branches.last().parent.halfLifeValue = ensdf.getHalfLifeValueParent(i).toDouble();
                decay.branches.last().parent.halfLifeUncery = ensdf.getHalfLifeUncertaintyParent(i).toDouble();
                decay.branches.last().parent.halfLifeUnit = ensdf.getHalfLifeUnitParent(i);
                decay.branches.last().parent.spinParity = ensdf.getSpinParityParent(i);
                decay.branches.last().transition = "BETA-";
                decay.branches.last().intensity = ensdf.getIntensityBeta(i,j);
            }else
            if(ensdf.findAlpha(i,j)) {
                decay.branches.last().parent.a = ensdf.getA_Parent(i).toInt();
                decay.branches.last().parent.z = ensdf.getZ_Parent(i);
                decay.branches.last().parent.symbol = ensdf.getParent(i);
                decay.branches.last().parent.halfLifeValue = ensdf.getHalfLifeValueParent(i).toDouble();
                decay.branches.last().parent.halfLifeUncery = ensdf.getHalfLifeUncertaintyParent(i).toDouble();
                decay.branches.last().parent.halfLifeUnit = ensdf.getHalfLifeUnitParent(i);
                decay.branches.last().parent.spinParity = ensdf.getSpinParityParent(i);
                decay.branches.last().transition = "ALPHA";
                decay.branches.last().intensity = ensdf.getIntensityAlpha(i,j);
                decay.branches.last().alpha_energy_kev = ensdf.getEnergyAlpha(i,j);
            }else
            if(ensdf.findEC(i,j)) {
                decay.branches.last().parent.a = ensdf.getA_Parent(i).toInt();
                decay.branches.last().parent.z = ensdf.getZ_Parent(i);
                decay.branches.last().parent.symbol = ensdf.getParent(i);
                decay.branches.last().parent.halfLifeValue = ensdf.getHalfLifeValueParent(i).toDouble();
                decay.branches.last().parent.halfLifeUncery = ensdf.getHalfLifeUncertaintyParent(i).toDouble();
                decay.branches.last().parent.halfLifeUnit = ensdf.getHalfLifeUnitParent(i);
                decay.branches.last().parent.spinParity = ensdf.getSpinParityParent(i);
                decay.branches.last().transition = "EC";
                decay.branches.last().intensity = ensdf.getIntensityTotalEC(i,j);
                decay.branches.last().ec.intensityEC = ensdf.getIntensityEC(i,j);
                decay.branches.last().ec.intensityBetaPlus= ensdf.getIntensityBetaPlus(i,j);
            }else {
                decay.branches.last().parent.a = ensdf.getA_Parent(i).toInt();
                decay.branches.last().parent.z = ensdf.getZ_Parent(i);
                decay.branches.last().parent.symbol = ensdf.getParent(i);
                decay.branches.last().parent.halfLifeValue = ensdf.getHalfLifeValueParent(i).toDouble();
                decay.branches.last().parent.halfLifeUncery = ensdf.getHalfLifeUncertaintyParent(i).toDouble();
                decay.branches.last().parent.halfLifeUnit = ensdf.getHalfLifeUnitParent(i);
                decay.branches.last().parent.spinParity = ensdf.getSpinParityParent(i);
                if(decay.branches.last().parent.symbol == decay.branches.last().daughter.symbol)
                    decay.branches.last().transition = "IT";
                else
                    decay.branches.last().transition = "GAMMA";
                decay.branches.last().intensity = ensdf.getGammaIntensity(i,j);
            }

            //gamma
            int noGammas = ensdf.countGammas(i,j);
            for(int g = 0; g<noGammas; g++){
                decay.branches.last().gammes << GammaModel();
                decay.branches.last().gammes.last().nuclide =
                //Nuclid
                decay.branches.last().gammes.last().nuclide = ensdf.getDaughter(i);
                //Initial level
                decay.branches.last().gammes.last().initialLevel_keV = ensdf.getLevelEnergy(i,j);
                //Final Level
                decay.branches.last().gammes.last().finalLevel_keV = ensdf.getFinalLevelEnergy(i,j,g);
                //energy g
                decay.branches.last().gammes.last().energy = ensdf.getGammaEnergy(i,j,g);
                //intensity g
                decay.branches.last().gammes.last().intensity = ensdf.getGammaIntensity(i,j,g);
                //multipolarity
                decay.branches.last().gammes.last().multipolarity = ensdf.getGammaMultipolarity(i,j,g);
                //electron convertion total
                decay.branches.last().gammes.last().totalElectronConverstion = ensdf.getGammaTotalElectronConvertion(i,j,g);
            }
        }
    }
    //end load into decay model

    loadENSDF();
}

void MainWindow::loadENSDF()
{
    int index = ui->selected_radionuclide_comboBox->findText(decay.radionuclide);

    if(index == -1) {
        ui->selected_radionuclide_comboBox->blockSignals(true);
        ui->selected_radionuclide_comboBox->addItem(decay.radionuclide);
        ui->selected_radionuclide_comboBox->blockSignals(false);
    }else {
        ui->selected_radionuclide_comboBox->blockSignals(true);
        ui->selected_radionuclide_comboBox->setCurrentIndex(index);
        ui->selected_radionuclide_comboBox->blockSignals(false);
    }

    //branches
    ToolWidget::clearTableWidget(ui->branches_tableWidget);
    for(int i=0; i<decay.branches.size(); i++) {
        QStringList row;
        row << decay.branches.at(i).parent.symbol
            << decay.branches.at(i).transition
            << decay.branches.at(i).intensity
            << decay.branches.at(i).level.excited_level_keV
            << decay.branches.at(i).daughter.symbol;
        ToolWidget::addRecord(ui->branches_tableWidget,row);

    }

    //gamma
    ToolWidget::clearTableWidget(ui->gamma_emissions_tableWidget);
    for(int i=0; i<decay.branches.size(); i++) {
        for(int j=0; j<decay.branches.at(i).gammes.size(); j++) {
            QStringList row;
            row << decay.branches.at(i).gammes.at(j).nuclide
                << decay.branches.at(i).gammes.at(j).initialLevel_keV
                << decay.branches.at(i).gammes.at(j).finalLevel_keV
                << decay.branches.at(i).gammes.at(j).energy
                << decay.branches.at(i).gammes.at(j).intensity
                << decay.branches.at(i).gammes.at(j).multipolarity
                << decay.branches.at(i).gammes.at(j).totalElectronConverstion;
            ToolWidget::addRecord(ui->gamma_emissions_tableWidget,row);
        }
    }
}


void MainWindow::on_branches_tableWidget_cellDoubleClicked(int row, int column)
{
    if(decay.branches.at(row).transition == "GAMMA" || decay.branches.at(row).transition == "IT")
        return;

    EditBranchDialog editBranch(this);
    editBranch.load(&decay.branches[row]);
    if(editBranch.exec() == QDialog::Accepted) {
        decay.branches[row] = editBranch.branch();
    }
}

