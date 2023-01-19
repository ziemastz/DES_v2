#ifndef FORMDASHBOARD_H
#define FORMDASHBOARD_H

#include <QWidget>
#include "Models/nuclidemodel.h"
#include "Models/branchmodel.h"

namespace Ui {
class FormDashboard;
}

class FormDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit FormDashboard(QWidget *parent = nullptr);
    ~FormDashboard();

private slots:
    void on_pushButton_importENSDF_clicked();

private:
    Ui::FormDashboard *ui;

    //data ui
    NuclideModel radionuclide;
    QList<BranchModel> branches;
};

#endif // FORMDASHBOARD_H
