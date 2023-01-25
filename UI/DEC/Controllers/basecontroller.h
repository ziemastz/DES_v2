#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "database.h"

class BaseController
{
public:
    BaseController();
protected:
    Database db;
    QString statement;
};

#endif // BASECONTROLLER_H
