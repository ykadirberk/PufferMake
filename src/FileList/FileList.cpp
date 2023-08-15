#include "FileList.h"

PufferMake::FileList::FileList() : m_filters(),  m_file_paths() {

}


PufferMake::FileList::~FileList() {

}

void PufferMake::FileList::AddFilterExtension(std::wstring_view ext) {
    m_filters.push_back(std::wstring(ext));
}

void PufferMake::FileList::TryAddFile(std::wstring_view file_path) {
    for (auto filter : m_filters ) {
        auto file_path_lengh = file_path.length();
        auto filter_length = filter.length();
        auto pos = file_path.find(L".");
        if (pos == std::wstring::npos) {
            continue;
        }
        std::wstring extension = std::wstring(file_path.substr(pos + 1));
        if (extension == filter) {
            m_file_paths.push_back(std::wstring(file_path));
            break;
        }
    }
}

void PufferMake::FileList::PrintFiles() {
    for (auto path : m_file_paths) {
        std::wcout << path << '\n';
    }
}