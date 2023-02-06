#ifndef GENERATESPECTRUMDIALOG_H
#define GENERATESPECTRUMDIALOG_H

#include <QDialog>
#include "Models/decayschememodel.h"
namespace Ui {
class GenerateSpectrumDialog;
}

class GenerateSpectrumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateSpectrumDialog(const DecaySchemeModel &radionuclideDecay, QWidget *parent = nullptr);
    ~GenerateSpectrumDialog();

private slots:
    void on_cancel_pushButton_clicked();

    void on_start_pushButton_clicked();

    void uintegerNumberLineEdit(const QString &arg1);

    void urealNumberLineEdit(const QString &arg1);

private:
    Ui::GenerateSpectrumDialog *ui;

    DecaySchemeModel decay;
};

#endif // GENERATESPECTRUMDIALOG_H
