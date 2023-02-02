#include "atomicdatadialog.h"
#include "ui_atomicdatadialog.h"
#include "atomicsubshelldialog.h"
#include <QPushButton>
#include "Controllers/atomicdatacontroller.h"
#include "toolwidget.h"

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

    connect(ui->radius_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->lineEdit_f12,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->lineEdit_f13,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->lineEdit_f23,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));

    connect(ui->intensity_w_lineEdit,SIGNAL(textChanged(QString)),this,SLOT(percentageNumberLineEdit(QString)));
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
    AtomicSubshellDialog subshellDialog(_symbol,pushButton->text(),this);

    subshellDialog.load(data.subshells.value(pushButton->text()));
    if(subshellDialog.exec() == QDialog::Accepted) {
        data.subshells.insert(pushButton->text(),subshellDialog.getData());
    }
}

void AtomicDataDialog::loadData()
{
    AtomicDataController atomicContr;
    data = atomicContr.getAtomicData(_symbol);

    ui->radius_lineEdit->setText(QString::number(data.radius));

    ui->lineEdit_f12->setText(QString::number(data.f12));
    ui->lineEdit_f13->setText(QString::number(data.f13));
    ui->lineEdit_f23->setText(QString::number(data.f23));

    reloadFluorescenceTable();

}

void AtomicDataDialog::on_cancel_pushButton_clicked()
{
    close();
}


void AtomicDataDialog::on_save_pushButton_clicked()
{
    AtomicDataController atomicContr;
    if(atomicContr.updateAtomicData(_symbol,data))
        qDebug() << "Saved atomic data";
}

void AtomicDataDialog::reloadFluorescenceTable()
{
    ToolWidget::clearTableWidget(ui->subshell_w_tableWidget);
    QStringList keys = data.fluorescenceYields.keys();
    std::sort(keys.begin(), keys.end());

    for(int i=0;i<keys.size();i++) {
        QStringList row;
        row << keys.at(i)
            << QString::number(data.fluorescenceYields.value(keys.at(i)));
        ToolWidget::addRecord(ui->subshell_w_tableWidget,row);
    }
}


void AtomicDataDialog::on_radius_lineEdit_editingFinished()
{
    data.radius = ui->radius_lineEdit->text().toDouble();
}


void AtomicDataDialog::on_lineEdit_f12_editingFinished()
{
    data.f12 = ui->lineEdit_f12->text().toDouble();
}


void AtomicDataDialog::on_lineEdit_f13_editingFinished()
{
     data.f13 = ui->lineEdit_f13->text().toDouble();
}


void AtomicDataDialog::on_lineEdit_f23_editingFinished()
{
     data.f23 = ui->lineEdit_f23->text().toDouble();
}


void AtomicDataDialog::on_addUpdate_subshell_pushButton_clicked()
{
    QString subshell = ui->subshell_w_comboBox->currentText();
    QString intensity = ui->intensity_w_lineEdit->text();
    if(subshell.isEmpty() || intensity.isEmpty())
        return;

    if(intensity.toDouble() == 0.0) {
        data.fluorescenceYields.remove(subshell);
    }else{
        data.fluorescenceYields.insert(subshell,intensity.toDouble());
    }
    reloadFluorescenceTable();
}

void AtomicDataDialog::urealNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }
}

void AtomicDataDialog::percentageNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }else if(line->text().toDouble() > 100) {
        line->setText("100");
    }
}

