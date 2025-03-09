#include "graphmanager.h"

GraphManager::GraphManager() {}

// ^^^ GraphManager / FileManager vvv

FileManager::FileManager() {}

bool FileManager::isExistingDir(const QString &path)
{
    QDir dir(path);
    if (dir.exists()){
        return true;
    }
    else{
        return false;
    }
}

bool FileManager::isExistingFile(const QString &path)
{
    return QFile::exists(path);
}
