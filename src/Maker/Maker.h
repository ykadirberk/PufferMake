#pragma once
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <future>
#include "../Configuration/Configuration.h"
#include "../FileList/FileList.h"

namespace PufferMake {
    class Maker {
        public:
            Maker();
            ~Maker();

            void Initialize();
            void LoadFiles();

            void PreProcess();
            void Compile();
            void Link();
            void Run();
            void Build();
            void BuildAndRun();

        private:
            FileList m_source_files;
            FileList m_header_files;
            FileList m_object_files;
            FileList m_preprocessed_files;
            FileList m_staticlib_files;
            FileList m_dynamiclib_files;

            void LoadFilters(std::vector<std::string>& filters, FileList& files);
            std::string RunProcess(const char* command);
            std::string GetFileNameWithoutExtension(std::string path);

            void PreProcessFile(std::wstring filename);
    };
}