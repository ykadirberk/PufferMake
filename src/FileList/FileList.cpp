#include "FileList.h"

PufferMake::FileList::FileList() : m_filters(),  m_file_paths() {

}


PufferMake::FileList::~FileList() {

}

void PufferMake::FileList::AddFilterExtension(std::wstring_view ext) {
    m_filters.push_back(std::wstring(ext));
}

void PufferMake::FileList::TryAddFile(std::wstring_view file_path) {
    for (const auto& filter : m_filters ) {
        auto file_path_lengh = file_path.length();
        auto filter_length = filter.length();
        auto pos = file_path.find(filter);
        if (pos == std::wstring::npos) {
            continue;
        }
        if (pos == file_path_lengh - filter_length) {
            m_file_paths.push_back(std::wstring(file_path));
        }
    }
}

void PufferMake::FileList::PrintFiles() {
    for (auto path : m_file_paths) {
        std::wcout << path << '\n';
    }
}