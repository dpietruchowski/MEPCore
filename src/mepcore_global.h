#ifndef MEPCORE_GLOBAL_H
#define MEPCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MEPCORE_LIBRARY)
#  define MEPCORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MEPCORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MEPCORE_GLOBAL_H
