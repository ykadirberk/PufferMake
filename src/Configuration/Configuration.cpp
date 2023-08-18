#include "Configuration.h"

PufferMake::Configuration::Configuration() : m_json_defaults(), m_json_build() {

}

PufferMake::Configuration::~Configuration() {
    
}

void PufferMake::Configuration::Initialize() {
    bool defaults_current = std::filesystem::exists("defaults.json");
    
    if (!defaults_current) {
        GenerateDefaults();
    }

    std::ifstream defaults("defaults.json");
    defaults >> m_json_defaults;
    auto vscode_integration = m_json_defaults["vs-code_integration"].get<bool>();
    if (vscode_integration) {
        VSCodeIntegration();
    }

    bool build_current = std::filesystem::exists("build.json");

    if (!build_current) {
        GenerateDefaultBuildConfig();
    }

    std::ifstream build("build.json");
    build >> m_json_build;

}

std::vector<std::string> PufferMake::Configuration::SourceFileFilters() {
    return m_json_defaults["source_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::HeaderFileFilters() {
    return m_json_defaults["header_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::ObjectFileFilters() {
    return m_json_defaults["object_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::PreprocessedFileFilters() {
    return m_json_defaults["preprocessed_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::StaticLibFileFilters() {
    return m_json_defaults["staticlib_file_filters"].get<std::vector<std::string>>();
}

std::vector<std::string> PufferMake::Configuration::DynamicLibFileFilters() {
    return m_json_defaults["dynamiclib_file_filters"].get<std::vector<std::string>>();
}

std::string PufferMake::Configuration::BuildName() {
    return m_json_build["build-name"].get<std::string>();
}
std::string PufferMake::Configuration::BuildType() {
    return m_json_build["build-type"].get<std::string>();
}
std::string PufferMake::Configuration::CppVersion() {
    return m_json_build["cpp-version"].get<std::string>();
}
std::string PufferMake::Configuration::Warnings() {
    return m_json_build["warnings"].get<std::string>();
}
std::string PufferMake::Configuration::Optimization() {
    if (!m_json_build["optimization"]["active"].get<bool>()) {
        return std::string();
    }
    return m_json_build["optimization"]["mode"].get<std::string>();
}
std::string PufferMake::Configuration::Debug() {
    if (!m_json_build["debug"]["active"].get<bool>()) {
        return std::string();
    }
    return m_json_build["debug"]["mode"].get<std::string>();
}
std::vector<std::string> PufferMake::Configuration::IncludeDirectories() {
    return m_json_build["include-directories"].get<std::vector<std::string>>();
}
PufferMake::__LinkingDetails PufferMake::Configuration::StaticLinking() {
    return {
        m_json_build["static-linking"]["active"].get<bool>(),
        m_json_build["static-linking"]["directories"].get<std::vector<std::string>>(), 
        m_json_build["static-linking"]["files"].get<std::vector<std::string>>()
    };
}
PufferMake::__LinkingDetails PufferMake::Configuration:: DynamicLinking() {
    return {
        m_json_build["dynamic-linking"]["active"].get<bool>(),
        m_json_build["dynamic-linking"]["directories"].get<std::vector<std::string>>(), 
        m_json_build["dynamic-linking"]["files"].get<std::vector<std::string>>()
    };
}

void PufferMake::Configuration::GenerateDefaults() {
    std::string js = R"({
    "vs-code_integration": true,
    "source_file_filters": [
        "c",
        "cc",
        "cpp",
        "CPP",
        "c++",
        "cp",
        "cxx"
    ],
    "header_file_filters": [
        "h",
        "hh",
        "hpp",
        "H"
    ],
    "object_file_filters": [
        "o"
    ],
    "preprocessed_file_filters": [
        "i",
        "ii"
    ],
    "staticlib_file_filters": [
        "a"
    ],
    "dynamiclib_file_filters": [
        "so"
    ],
    "comments": {
        "explanation": "# This comment section is to explain both build.json and defaults.json",
        "defaults": "# You probably shouldn't change this file.",
        "defaults-2": "# This file is needed for the make to work properly.",
        "build.json": {
            "build-name": "# Name of produced software, no need for extension.",
            "build-type": "executable, shared, static",
            "cpp-version": "# in form of c++20",
            "warnings": "disabled, all, extra",
            "optimization.active": "# true to enable",
            "optimization.mode": "O0, O1, O2, O3, Os, Ofast, Og, Oz",
            "debug.active": "# true to enable",
            "debug.mode": "g0, g1, g, g3, ggdb, gdwarf",
            "include-directories": "# list of include directories",
            "static-linking.active": "# true to enable",
            "static-linking.directories": "# list of static library directories",
            "static-linking.files": "# list of library file names",
            "dynamic-linking.active": "# true to enable",
            "dynamic-linking.directories": "# list of dynamic library directories",
            "dynamic-linking.files": "# list of library file names"
        }
    }
})";

    std::ofstream output("defaults.json");
    output << js << std::endl;
}

void PufferMake::Configuration::VSCodeIntegration() {
    bool codefolder_current = std::filesystem::exists(".vscode");
    if (!codefolder_current) {
        std::filesystem::create_directory(".vscode");
        bool tasks_current = std::filesystem::exists(".vscode/tasks.json");
        if (!tasks_current) {
            using namespace nlohmann::literals;
            std::string js = R"({
	"version": "2.0.0",
	"tasks": [
		{
            "label": "Compile",
            "type": "shell",
            "command": "./PufferMake compile",
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
        },
        {
            "label": "Link Executable",
            "type": "shell",
			"command": "./PufferMake link-executable",
            "problemMatcher": [],
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
        },
        {
            "label": "Link Shared Library",
            "type": "shell",
			"command": "./PufferMake link-shared",
            "problemMatcher": [],
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
        },
        {
            "label": "Link Static Library",
            "type": "shell",
			"command": "./PufferMake link-static",
            "problemMatcher": [],
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
        },
        {
            "label": "Run",
            "type": "shell",
            "command": "./PufferMake run",
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
        },
		{
			"label": "Build",
			"type": "shell",
			"command": "./PufferMake build",
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
		},
		{
			"label": "Build & Run",
			"type": "shell",
			"command": "./PufferMake build-run",
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
		},
        {
            "label": "Generate Preprocessed",
            "type": "shell",
            "command": "./PufferMake preprocess",
			"presentation": {
				"echo": true,
				"reveal": "always",
				"focus": true,
				"panel": "new",
				"showReuseMessage": true,
				"clear": true
			}
        }
	]
})";   
            std::ofstream tasks(".vscode/tasks.json");
            tasks << js << std::endl;
        }
    }
}

void PufferMake::Configuration::GenerateDefaultBuildConfig() {
    nlohmann::json j;
    std::string js = R"({
    "build-name": "app",
    "build-type": "executable",
    "cpp-version": "c++20",
    "warnings": "all",
    "optimization": {
        "active": true,
        "mode": "Og"
    },
    "debug": {
        "active": true,
        "mode": "ggdb"
    },
    "include-directories": [],
    "static-linking": {
        "active": false,
        "directories": [],
        "files": []
    },
    "dynamic-linking": {
        "active": false,
        "directories": [],
        "files": []
    }
})";
    std::ofstream output("build.json", std::ios::trunc);
    output << js << std::endl;
}