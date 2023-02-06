#ifndef GENERATESPECTRUMDIALOG_H
#define GENERATESPECTRUMDIALOG_H

#include <QDialog>

namespace Ui {
class GenerateSpectrumDialog;
}

class GenerateSpectrumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateSpectrumDialog(QWidget *parent = nullptr);
    ~GenerateSpectrumDialog();

private:
    Ui::GenerateSpectrumDialog *ui;
};

#endif // GENERATESPECTRUMDIALOG_H
