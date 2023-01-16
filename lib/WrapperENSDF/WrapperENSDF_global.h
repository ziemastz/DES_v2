#ifndef WRAPPERENSDF_GLOBAL_H
#define WRAPPERENSDF_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QDebug>
#include <QString>
#include <QStringRef>
#include <QFile>
#include <QTextStream>

#if defined(WRAPPERENSDF_LIBRARY)
#  define WRAPPERENSDF_EXPORT Q_DECL_EXPORT
#else
#  define WRAPPERENSDF_EXPORT Q_DECL_IMPORT
#endif

#endif // WRAPPERENSDF_GLOBAL_H
