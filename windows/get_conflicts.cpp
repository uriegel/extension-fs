#include <windows.h>
#include <string>
#include <vector>
#include "get_conflicts.h"
#include "utils.h"
using namespace std;

void get_conflicts(const wstring& sourcePath, const wstring& targetPath, const wstring& subPath, 
                    const WIN32_FIND_DATAW& sourceInfo, vector<Conflict_item>& conflicts) {
    auto isDir = (sourceInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
    if (isDir) {
        // TODO: (2) Alle Dateien und Ordner ermitteln und diese Funktion rekursiv aufrufen
    } else {
        auto path = combine_path(targetPath, sourceInfo.cFileName);
        WIN32_FILE_ATTRIBUTE_DATA targetInfo;
        if (GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &targetInfo)) {
            conflicts.emplace_back(Conflict_item {
                sourceInfo.cFileName,
                static_cast<uint64_t>(sourceInfo.nFileSizeHigh) << 32 | sourceInfo.nFileSizeLow,
                convert_windowstime_to_unixtime(sourceInfo.ftLastWriteTime),
                {0},
                static_cast<uint64_t>(targetInfo.nFileSizeHigh) << 32 | targetInfo.nFileSizeLow,
                convert_windowstime_to_unixtime(targetInfo.ftLastWriteTime),
                {0}
            });
        }
    }
}

void get_conflicts(const wstring& sourcePath, const wstring& targetPath, const vector<wstring> items, 
    vector<Conflict_item>& conflicts) {
    
    for (auto i = 0U; i < items.size(); i++) {
        auto path = combine_path(sourcePath, items[i]);
        WIN32_FIND_DATAW w32fd{ 0 };
        auto ret = FindFirstFileW(path.c_str(), &w32fd);
        get_conflicts(sourcePath, targetPath, L"", w32fd, conflicts);
        FindClose(ret);
    }
}