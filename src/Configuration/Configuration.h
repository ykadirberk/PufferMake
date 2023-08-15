#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include "../nlohmann/json.hpp"

namespace PufferMake {
    class Configuration {
        public:
            Configuration();
            ~Configuration();

            void Initialize();

            std::vector<std::string> SourceFileFilters();
            std::vector<std::string> HeaderFileFilters();
            std::vector<std::string> ObjectFileFilters();
            std::vector<std::string> PreprocessedFileFilters();
            std::vector<std::string> StaticLibFileFilters();
            std::vector<std::string> DynamicLibFileFilters();


        private:
            nlohmann::json json_object;

            void GenerateConfig();
            void VSCodeIntegration();
    };

}