#ifndef NUCLIDECONTROLLER_H
#define NUCLIDECONTROLLER_H
#include "Controllers/basecontroller.h"
#include "Models/nuclidemodel.h"
class NuclideController : public BaseController
{
public:
    NuclideController();
    NuclideModel getNuclide(const QString &symbol);
    QStringList getNuclides();
    QString getStandardFormatHalfLifeUnit(const QString &unit);
    QStringList getStandardFormatHalfLifeUnits();
};

#endif // NUCLIDECONTROLLER_H
