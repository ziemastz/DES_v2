#ifndef FORMNUCLIDE_H
#define FORMNUCLIDE_H

#include <QWidget>

namespace Ui {
class FormNuclide;
}

class FormNuclide : public QWidget
{
    Q_OBJECT

public:
    explicit FormNuclide(QWidget *parent = nullptr);
    ~FormNuclide();

private:
    Ui::FormNuclide *ui;
};

#endif // FORMNUCLIDE_H
