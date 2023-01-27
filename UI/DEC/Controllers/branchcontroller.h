#ifndef BRANCHCONTROLLER_H
#define BRANCHCONTROLLER_H

#include "Controllers/basecontroller.h"
#include "Models/branchmodel.h"

class BranchController : public BaseController
{
public:
    BranchController();
    QVector<BranchModel> getBranches(const QString &nuclide);
    bool updateBranches(const QString &radionuclide, const QVector<BranchModel> &branches);

};

#endif // BRANCHCONTROLLER_H
