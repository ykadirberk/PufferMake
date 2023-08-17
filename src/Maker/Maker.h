#pragma once
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <string_view>
#include <string>
#include <future>
#include "../Configuration/Configuration.h"
#include "../FileList/FileList.h"
#include "../Colour/Colour.h"

namespace PufferMake {
    class Maker {
        public:
            Maker();
            ~Maker();

            void Initialize();
            void LoadFiles();

            void ExecuteInstruction(std::string_view instruction);

            void PreProcess();
            void Compile();
            void LinkExecutable();
            void LinkShared();
            void LinkStatic();
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

            Configuration m_config;

            std::filesystem::path m_current_working_directory;

            void LoadFilters(std::vector<std::string>& filters, FileList& files);
            std::string RunProcess(const char* command);
            std::string GetFileNameWithoutExtension(std::string path);


            // Thread methods
            void PreProcessFile(std::wstring current_name);
            void CompileFile(std::wstring current_name);
    };
}