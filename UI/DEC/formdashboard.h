#ifndef FORMDASHBOARD_H
#define FORMDASHBOARD_H

#include <QWidget>

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
};

#endif // FORMDASHBOARD_H
