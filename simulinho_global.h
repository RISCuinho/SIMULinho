#ifndef RISCUNHO_GLOBAL_H
#define RISCUNHO_GLOBAL_H

#include <QtCore/QtGlobal>

/*
 * https://doc.qt.io/qt-5/sharedlibrary.html
 * https://wiki.qt.io/How_to_create_a_library_with_Qt_and_use_it_in_an_application
 */
#if defined(RISCUINHO_SHAREDLIB)
#  define RISCUINHO_SHAREDLIB_EXPORT Q_DECL_EXPORT
#else
#  define RISCUINHO_SHAREDLIB_EXPORT Q_DECL_IMPORT
#endif


#endif // RISCUNHO_GLOBAL_H
