#include "formnuclide.h"
#include "ui_formnuclide.h"

FormNuclide::FormNuclide(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormNuclide)
{
    ui->setupUi(this);
}

FormNuclide::~FormNuclide()
{
    delete ui;
}
