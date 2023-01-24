#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "database.h"

class BaseController
{
public:
    BaseController();
protected:
    Database db;
};

#endif // BASECONTROLLER_H
