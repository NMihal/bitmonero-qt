#ifndef UTILS_H
#define UTILS_H

#include <QStringList>
#include <QFileInfo>
#include <QDebug>

class Utils
{
public:
    Utils();

    /* Returns first executable pFilenames found in pPaths */
    static const QStringList findExecutables(const QStringList& pPaths, const QStringList& pFilenames, bool pFindOne = false);

    static const QStringList getStandardSearchPaths();

    static const QStringList findWalletsKeysFiles(const QUrl &pUrl, const QString& pFileSuffix = ".keys");


};

#endif // UTILS_H
