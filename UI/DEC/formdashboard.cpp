#include "formdashboard.h"
#include "ui_formdashboard.h"
#include <QFileDialog>
#include "libensdfreader.h"

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
    QString ensdf_path = QFileDialog::getOpenFileName(this,tr("Select ENSDF"),QDir::homePath());

    if(ensdf_path.isEmpty())
        return;

    LibENSDFReader reader;

    reader.load(ensdf_path);

}

