#ifndef WRAPPERENSDF_H
#define WRAPPERENSDF_H
/******************************************************************************
 * Library name:        WrapperENSDF
 * Author:              Tomasz Ziemek, POLATOM, Poland
 * Date:                16.01.2023
 * Qt version:          5.15.2
 *
 * Description:         Library for reading nuclear data contained in ENSDF
 *                      files.
 * Version:             1.0.0
 *
 * Change log:          1.0.1
 *
 *
 ******************************************************************************
 */
#include "WrapperENSDF_global.h"
#include "ensdf.h"
#include "recordensdf.h"

class WRAPPERENSDF_EXPORT WrapperENSDF
{
public:
    WrapperENSDF(const QString &filename);

    bool read();

private:
    QVector<ENSDF> raw;
    QString _filename;
    bool wrap(const RecordENSDF &line);
    bool isBlank(const RecordENSDF &str);
    bool isBlank(const QString &str);

};

#endif // WRAPPERENSDF_H
