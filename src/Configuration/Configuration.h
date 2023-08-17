#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include "../nlohmann/json.hpp"

namespace PufferMake {
    class __LinkingDetails {
        public:
            __LinkingDetails(
                bool act,
                std::vector<std::string> dir, 
                std::vector<std::string> fil) :
                    active(act), directories(dir), files(fil) {}
            bool active;
            std::vector<std::string> directories;
            std::vector<std::string> files;
    };

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

            std::string BuildName();
            std::string BuildType();
            std::string CppVersion();
            std::string Warnings();
            std::string Optimization();
            std::string Debug();
            std::vector<std::string> IncludeDirectories();
            __LinkingDetails StaticLinking();
            __LinkingDetails DynamicLinking();

        private:
            nlohmann::json m_json_defaults;
            nlohmann::json m_json_build;

            void GenerateDefaults();
            void VSCodeIntegration();
            void GenerateDefaultBuildConfig();
    };

}