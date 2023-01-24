#ifndef ATOMICDATACONTROLLER_H
#define ATOMICDATACONTROLLER_H

#include "Controllers/basecontroller.h"
#include "Models/atomicdatamodel.h"

class AtomicDataController : public BaseController
{
public:
    AtomicDataController();
    AtomicDataModel getAtomicData(const QString &nuclide);

};

#endif // ATOMICDATACONTROLLER_H
