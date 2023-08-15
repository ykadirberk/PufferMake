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
    if (vscode_integration) {
        VSCodeIntegration();
    }
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

std::vector<std::string> PufferMake::Configuration::StaticLibFileFilters() {
    return json_object["staticlib_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::DynamicLibFileFilters() {
    return json_object["dynamiclib_file_filters"].get<std::vector<std::string>>();
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

    j["staticlib_file_filters"] = {
        "a"
    };

    j["dynamiclib_file_filters"] = {
        "so",
    };

    std::ofstream output("config.json");
    output << std::setw(4) << j << std::endl;
}

void PufferMake::Configuration::VSCodeIntegration() {
    bool codefolder_current = std::filesystem::exists(".vscode");
    if (!codefolder_current) {
        std::filesystem::create_directory(".vscode");
        bool tasks_current = std::filesystem::exists(".vscode/tasks.json");
        if (!tasks_current) {
            using namespace nlohmann::literals;
            nlohmann::json js = R"({
	"version": "2.0.0",
	"tasks": [
	  	{
			"label": "Run tests",
			"type": "shell",
			"command": "./scripts/test.sh",
			"group": "test",
			"presentation": {
		  		"reveal": "always",
		  		"panel": "new"
			}
	  	}
	]
})"_json;   
            std::ofstream tasks(".vscode/tasks.json");
            tasks << std::setw(4) << js << std::endl;
        }
    }
}