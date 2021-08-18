#ifndef SIMULINHO_VPI_GLOBAL_H
#define SIMULINHO_VPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIMULINHO_VPI_LIBRARY)
#  define SIMULINHO_VPISHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIMULINHO_VPISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIMULINHO_VPI_GLOBAL_H
