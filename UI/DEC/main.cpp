
#include "mainwindow.h"

#include <QApplication>
/*  ***************************************************************************
 *  Software name:  Decay Energy Spectra
 *        Authors:  Tomasz Ziemek, POLATOM, Poland
 *    Description:  Generation decay energy spectrum of radionuclide
 *
 *    Create date:  12.01.2023
 *  ***************************************************************************
 *  Upgrade
 *  v1.0.1:
 *      - Import dateset of radionuclide from ENSDF
 *  v1.0.2:
 *      - Fixed calculation of electron conversion intensity
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("DES");
    QApplication::setApplicationVersion("v1.0.2");

    MainWindow w;
    w.show();
    return a.exec();
}
