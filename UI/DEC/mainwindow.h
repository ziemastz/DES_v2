#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Models/decayschememodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_import_ensdf_pushButton_clicked();

    void on_branches_tableWidget_cellDoubleClicked(int row, int column);

    void on_selected_radionuclide_comboBox_currentTextChanged(const QString &arg1);

    void on_save_data_pushButton_clicked();

    void on_gamma_emissions_tableWidget_cellDoubleClicked(int row, int column);

    void on_generate_spectrumpushButton_clicked();

private:
    Ui::MainWindow *ui;

    DecaySchemeModel decay;

    void loadENSDF();

    void load(const QString &nuclide);

    QString findForbiddenness(const QString &forbiddenness, const QString &logft);

};
#endif // MAINWINDOW_H
