#include "atomicsubshelldialog.h"
#include "ui_atomicsubshelldialog.h"
#include "toolwidget.h"

AtomicSubshellDialog::AtomicSubshellDialog(const QString &symbol, const QString &subshell, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AtomicSubshellDialog),
    _symbol(symbol),
    _subshell(subshell)
{
    ui->setupUi(this);

    ui->groupBox_main->setTitle(subshell + " - Subshell");
    ui->label_titleApp->setText("Atomic Subshell "+subshell+" of "+symbol);

    ui->label_vacancy->setText(subshell);
    ui->label_vacancy_x->setText(subshell);

    ui->comboBox_occupancy->addItems(data.getSubshells(subshell));
    ui->comboBox_occupancy_x->addItems(data.getSubshells(subshell));

    connect(ui->lineEdit_energy,SIGNAL(textChanged(QString)),this,SLOT(urealNumberLineEdit(QString)));
    connect(ui->lineEdit_electrons,SIGNAL(textChanged(QString)),this,SLOT(uintegerNumberLineEdit(QString)));
    connect(ui->lineEdit_intensity,SIGNAL(textChanged(QString)),this,SLOT(percentageNumberLineEdit(QString)));
    connect(ui->lineEdit_intensity_x,SIGNAL(textChanged(QString)),this,SLOT(percentageNumberLineEdit(QString)));
}

AtomicSubshellDialog::~AtomicSubshellDialog()
{
    delete ui;
}

void AtomicSubshellDialog::load(const AtomicSubshellModel &loadData)
{
    data = loadData;

    ui->lineEdit_energy->setText(QString::number(data.binding_energy_keV));
    ui->lineEdit_electrons->setText(QString::number(data.elektrons_max));

    reloadAugerTable();
    reloadXRayTable();
}

void AtomicSubshellDialog::on_comboBox_occupancy_currentTextChanged(const QString &arg1)
{
    QString current_emitting = ui->comboBox_emitting->currentText();

    ui->comboBox_emitting->clear();
    ui->comboBox_emitting->addItem(arg1);
    ui->comboBox_emitting->addItems(data.getSubshells(arg1));
    ui->comboBox_emitting->setCurrentIndex(ui->comboBox_emitting->findText(current_emitting));
}

void AtomicSubshellDialog::reloadAugerTable()
{
    ToolWidget::clearTableWidget(ui->tableWidget_auger);
    QStringList keys = data.auger.keys();
    std::sort(keys.begin(), keys.end());

    for(int i=0;i<keys.size();i++) {
        QStringList row;
        row << keys.at(i)
            << QString::number(data.auger.value(keys.at(i)));
        ToolWidget::addRecord(ui->tableWidget_auger,row);
    }
}

void AtomicSubshellDialog::reloadXRayTable()
{
    ToolWidget::clearTableWidget(ui->tableWidget_xRay);
    QStringList keys = data.xRay.keys();
    std::sort(keys.begin(), keys.end());

    for(int i=0;i<keys.size();i++) {
        QStringList row;
        row << keys.at(i)
            << QString::number(data.xRay.value(keys.at(i)));
        ToolWidget::addRecord(ui->tableWidget_xRay,row);
    }
}

AtomicSubshellModel AtomicSubshellDialog::getData() const
{
    return data;
}


void AtomicSubshellDialog::on_pushButton_addAugerTransition_clicked()
{
    if(ui->comboBox_occupancy->currentText().isEmpty() || ui->comboBox_emitting->currentText().isEmpty() || ui->lineEdit_intensity->text().isEmpty()) {
        return;
    }
    QString transition = QString("%1 %2 %3").arg(ui->label_vacancy->text(),ui->comboBox_occupancy->currentText(),ui->comboBox_emitting->currentText());
    QString intensity = ui->lineEdit_intensity->text();

    if(intensity.toDouble() == 0.0) {
        data.auger.remove(transition);
    }else {
        data.auger.insert(transition,intensity.toDouble());
    }

    reloadAugerTable();
}


void AtomicSubshellDialog::on_pushButton_addXRayTransition_clicked()
{
    if(ui->comboBox_occupancy_x->currentText().isEmpty() || ui->lineEdit_intensity_x->text().isEmpty()) {
        return;
    }
    QString transition = QString("%1 %2").arg(ui->label_vacancy_x->text(),ui->comboBox_occupancy_x->currentText());
    QString intensity = ui->lineEdit_intensity_x->text();

    if(intensity.toDouble() == 0.0) {
        data.xRay.remove(transition);
    }else {
        data.xRay.insert(transition,intensity.toDouble());
    }

    reloadXRayTable();
}


void AtomicSubshellDialog::on_cancel_pushButton_clicked()
{
    close();
}


void AtomicSubshellDialog::on_save_pushButton_clicked()
{
    accept();
}

void AtomicSubshellDialog::urealNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }
}

void AtomicSubshellDialog::uintegerNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::integerNumberModeLineEdit(arg1,line);
    if(line->text().toInt() < 0) {
        line->setText("0");
    }
}

void AtomicSubshellDialog::percentageNumberLineEdit(const QString &arg1)
{
    QLineEdit *line = (QLineEdit *)sender();
    ToolWidget::realNumberModeLineEdit(arg1,line);
    if(line->text().toDouble() < 0) {
        line->setText("0");
    }else if(line->text().toDouble() > 100) {
        line->setText("100");
    }
}


void AtomicSubshellDialog::on_lineEdit_energy_editingFinished()
{
    data.binding_energy_keV = ui->lineEdit_energy->text().toDouble();
}


void AtomicSubshellDialog::on_lineEdit_electrons_editingFinished()
{
    data.elektrons_max = ui->lineEdit_electrons->text().toInt();
}

