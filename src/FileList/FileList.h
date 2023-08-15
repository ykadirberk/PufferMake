#pragma once
#include <iostream>
#include <string_view>
#include <string>
#include <vector>

namespace PufferMake {
    class FileList {
        public:
            FileList();
            ~FileList();

            void AddFilterExtension(std::wstring_view ext);

            void TryAddFile(std::wstring_view file_path);

            std::vector<std::wstring> RetrieveFileList();

            void PrintFiles();
            
        private:
            std::vector<std::wstring> m_filters;
            std::vector<std::wstring> m_file_paths;
    };
}