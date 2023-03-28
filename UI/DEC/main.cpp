
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
 *  v1.1.0:
 *      - Add Beta+ data
 *
 *  v1.0.1:
 *      - Import dateset of radionuclide from ENSDF
 *  v1.0.2:
 *      - Fixed calculation of electron conversion intensity
 *  v1.0.3:
 *      - Remove from branches 'GAMMA' transitions
 *      - Fixed the randomization of gamma transitions
 *  v1.0.4:
 *      - Add beta transition
 *  v1.0.5:
 *      - Fix Beta spectrum
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("DES");
    QApplication::setApplicationVersion("v1.1.0");

    MainWindow w;
    w.show();
    return a.exec();
}
