#include "Configuration.h"

PufferMake::Configuration::Configuration() : json_object() {

}


PufferMake::Configuration::~Configuration() {
    
}


void PufferMake::Configuration::Initialize() {
    bool config_current = std::filesystem::exists("config.json");
    if (!config_current) {
        GenerateConfig();
    }
    std::ifstream config("config.json");
    config >> json_object;
    auto vscode_integration = json_object["vs-code_integration"].get<bool>();
    
}

std::vector<std::string> PufferMake::Configuration::SourceFileFilters() {
    return json_object["source_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::HeaderFileFilters() {
    return json_object["header_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::ObjectFileFilters() {
    return json_object["object_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::PreprocessedFileFilters() {
    return json_object["preprocessed_file_filters"].get<std::vector<std::string>>();
}

void PufferMake::Configuration::GenerateConfig() {
    nlohmann::json j;
    j["vs-code_integration"] = true;
    j["source_file_filters"] = {
        "c",
        "cc",
        "cpp",
        "CPP",
        "c++",
        "cp",
        "cxx"
    };

    j["header_file_filters"] = {
        "h",
        "hh",
        "hpp",
        "H"
    };

    j["object_file_filters"] = {
        "o"
    };

    j["preprocessed_file_filters"] = {
        "i",
        "ii"
    };
    std::ofstream output("config.json");
    output << std::setw(4) << j << std::endl;
}