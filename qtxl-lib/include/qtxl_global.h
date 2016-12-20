#ifndef QTXL_GLOBAL_H
#define QTXL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTXL_LIBRARY)
#  define QTXLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTXLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTXL_GLOBAL_H
