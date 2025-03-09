#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "precompiled.h"

class GraphManager
{
public:
    GraphManager();
};

class FileManager
{
public:
    FileManager();
    static bool isExistingDir(const QString& path);
    static bool isExistingFile(const QString& path);
};

#endif // GRAPHMANAGER_H
