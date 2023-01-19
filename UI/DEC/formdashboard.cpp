#include "formdashboard.h"
#include "ui_formdashboard.h"
#include <QFileDialog>
#include "wrapperensdf.h"
#include "Models/nuclidemodel.h".h"

FormDashboard::FormDashboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDashboard)
{
    ui->setupUi(this);
}

FormDashboard::~FormDashboard()
{
    delete ui;
}

void FormDashboard::on_pushButton_importENSDF_clicked()
{
    //select ensdf
    QString ensdf_path = QFileDialog::getOpenFileName(this,tr("Select ENSDF"),QDir::homePath());

    if(ensdf_path.isEmpty())
        return;

    //read ensdf
    WrapperENSDF wrapper(ensdf_path);
    if(!wrapper.read()) {
        qDebug() << "Failed to load data from ENSDF";
        return;
    }

    // load radionuclide data from ensdf
    radionuclide.setSymbol(wrapper.getParent());
    radionuclide.setHalfLifeValue(wrapper.getHalfLifeValueParent());
    radionuclide.setHalfLifeUncertainty(wrapper.getHalfLifeUncertaintyParent());
    radionuclide.setHalfLifeUnit(wrapper.getHalfLifeUnitParent());

    radionuclide.setSpinParity(wrapper.getSpinParityParent());

    // load data in ui
    ui->comboBox_schemeRadionuclide->addItem(wrapper.getParent());

    int noDaughters = wrapper.countDaughters();
    for(int i = 0; i < noDaughters; i++) {
        int noLevels = wrapper.countLevels(i);
        for(int j = 0; j < noLevels; j++) {
            if(wrapper.findBeta(i,j)) {
                QStringList branchRecord;
                //grantdaughter
                branchRecord << "-";
                //parent
                branchRecord << wrapper.getParent(i);
                //transition
                branchRecord << "Beta-";
                //intensity
                branchRecord << wrapper.getIntensityBeta(i,j);
                // excited level
                branchRecord << wrapper.getLevelEnergy(i,j);
                //daughter
                branchRecord << wrapper.getDaughter(i);

                int row = ui->tableWidget_branches->rowCount();
                ui->tableWidget_branches->insertRow(row);
                for(int k = 0; k<branchRecord.count(); k++)
                {
                    ui->tableWidget_branches->setItem(row,k,new QTableWidgetItem(branchRecord.at(k)));
                }
            }

            //gamma emissions
            int noGammas = wrapper.countGammas(i,j);
            for(int g = 0; g<noGammas; g++){
                QStringList gammaRecord;
                //Nuclid
                gammaRecord << wrapper.getDaughter(i);
                //Initial level
                gammaRecord << wrapper.getLevelEnergy(i,j);
                //Final Level
                gammaRecord << wrapper.getFinalLevelEnergy(i,j,g);
                //energy g
                gammaRecord << wrapper.getGammaEnergy(i,j,g);
                //intensity g
                gammaRecord << wrapper.getGammaIntensity(i,j,g);
                //multipolarity
                gammaRecord << wrapper.getGammaMultipolarity(i,j,g);
                //electron convertion total
                gammaRecord << wrapper.getGammaTotalElectronConvertion(i,j,g);

                int row = ui->tableWidget_gammaEmissions->rowCount();
                ui->tableWidget_gammaEmissions->insertRow(row);
                for(int k = 0; k<gammaRecord.count(); k++)
                {
                    ui->tableWidget_gammaEmissions->setItem(row,k,new QTableWidgetItem(gammaRecord.at(k)));
                }

            }
        }
    }


}

