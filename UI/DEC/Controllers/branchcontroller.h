#ifndef BRANCHCONTROLLER_H
#define BRANCHCONTROLLER_H

#include "Controllers/basecontroller.h"
#include "Models/branchmodel.h"

class BranchController : public BaseController
{
public:
    BranchController();
    QVector<BranchModel> getBranches(const QString &nuclide);


};

#endif // BRANCHCONTROLLER_H
