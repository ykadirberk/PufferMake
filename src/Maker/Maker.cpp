#include "Maker.h"

PufferMake::Maker::Maker() : m_source_files(),
                             m_header_files(),
                             m_object_files(),
                             m_preprocessed_files(),
                             m_staticlib_files(),
                             m_dynamiclib_files(),
                             m_config() {
    m_current_working_directory = std::filesystem::current_path();
}

PufferMake::Maker::~Maker() {

}

void PufferMake::Maker::Initialize() {
    m_config.Initialize();

    auto source_file_filters = m_config.SourceFileFilters();
    auto header_file_filters = m_config.HeaderFileFilters();
    auto object_file_filters = m_config.ObjectFileFilters();
    auto preprocessed_file_filters = m_config.PreprocessedFileFilters();
    auto staticlib_file_filters = m_config.StaticLibFileFilters();
    auto dynamiclib_file_filters = m_config.DynamicLibFileFilters();

    LoadFilters(source_file_filters,        m_source_files);
    LoadFilters(header_file_filters,        m_header_files);
    LoadFilters(object_file_filters,        m_object_files);
    LoadFilters(preprocessed_file_filters,  m_preprocessed_files);
    LoadFilters(staticlib_file_filters,     m_staticlib_files);
    LoadFilters(dynamiclib_file_filters,    m_dynamiclib_files);

}

void PufferMake::Maker::LoadFiles() {

    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(m_current_working_directory)) {
        if (dir_entry.is_directory()) {
            continue;
        }

        auto current_path = dir_entry.path().wstring();

        m_source_files.         TryAddFile(current_path);
        m_header_files.         TryAddFile(current_path);
        //m_object_files.         TryAddFile(current_path);
        m_preprocessed_files.   TryAddFile(current_path);
        m_staticlib_files.      TryAddFile(current_path);
        m_dynamiclib_files.     TryAddFile(current_path);
    }
}

void PufferMake::Maker::ExecuteInstruction(std::string_view instruction) {
    std::string inst(instruction);
    if (inst == "preprocess") {
        this->PreProcess();
    }
    if (inst == "compile") {
        this->Compile();
    }
    if (inst == "link-executable") {
        this->LinkExecutable();
    }
    if (inst == "link-shared") {

    }
    if (inst == "run") {
        this->Run();
    }
    if (inst == "build") {
        this->Build();
    }
    if (inst == "build-run") {
        this->BuildAndRun();
    }
}

void PufferMake::Maker::PreProcess() {
    std::cout 
        << COLOUR_YELLOW_B << "Starting preprocess..." 
        << COLOUR_RESET << std::endl;
    bool preprocessed_current = std::filesystem::exists("./preprocessed");
    if (!preprocessed_current) {
        std::filesystem::create_directory("preprocessed");
    }
    std::vector<std::future<void>> futures;
    auto temp_file_name_list = m_source_files.RetrieveFileList();
    for (auto name : temp_file_name_list) {
        futures.push_back(
            std::async(
                std::launch::async, 
                &PufferMake::Maker::PreProcessFile, 
                this, 
                name
            )
        );
    }

    for (auto& f : futures) {
        f.wait();
    }
    std::cout << "Finished preprocessing" << std::endl;
}

void PufferMake::Maker::Compile() {
    std::cout 
        << COLOUR_BLUE_B << "Starting compilation..." 
        << COLOUR_RESET << std::endl;
    bool preprocessed_current = std::filesystem::exists("./objects");
    if (!preprocessed_current) {
        std::filesystem::create_directory("objects");
    }
    auto cwd = std::filesystem::current_path();
    std::filesystem::current_path("./objects");

    auto temp_file_name_list = m_source_files.RetrieveFileList();
    std::vector<std::future<void>> futures;
    for (auto name : temp_file_name_list) {
        futures.push_back(
            std::async(
                std::launch::async,
                &PufferMake::Maker::CompileFile,
                this,
                name
            )
        );
    }

    for (auto& f : futures) {
        f.wait();
    }

    std::filesystem::current_path(m_current_working_directory);

    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(m_current_working_directory.string())) {
        if (dir_entry.is_directory()) {
            continue;
        }
        auto current_path = dir_entry.path().wstring();
        m_object_files.TryAddFile(current_path);
    }

    std::cout << "Finished compiling." << std::endl;
}

void PufferMake::Maker::LinkExecutable() {
    std::cout 
        << COLOUR_MAGENTA_B << "Starting linking for executable..." 
        << COLOUR_RESET << std::endl;


    // g++ objects/main.o objects/FileList.o objects/Configuration.o objects/ParseCommand.o objects/Maker.o -o ./target/app -lstdc++fs
    auto temp_file_name_list = m_object_files.RetrieveFileList();
    std::stringstream command;
    command << "g++ ";
    for (auto name : temp_file_name_list) {
        std::string converted(name.begin(), name.end());
        command << '\"' << converted << "\" ";
    }
    
    command << "-o ./target/";
    auto build_name = m_config.BuildName();
    if (build_name.length() != 0) {
        command  << build_name;
    } else {
        command << "app";
    }
    bool target_folder_current = std::filesystem::exists("./target");
    if (!target_folder_current) {
        std::filesystem::create_directory("./target");
    }
    std::string result = RunProcess(command.str().data());

    std::cout << "Finished linking for executable." << std::endl;
}

void PufferMake::Maker::LinkShared() {

}
void PufferMake::Maker::LinkStatic() {

}

void PufferMake::Maker::Run() {
    auto build_type = m_config.BuildType();
    if (build_type != "executable") {
        std::cout
            << COLOUR_WHITE_B
            << "Build type should be \"executable\" for run operation."
            << COLOUR_RESET << std::endl;
        return;
    } 
    auto build_name = m_config.BuildName();
    std::string executable = "./target/";
    executable += build_name;
    auto result = std::system(executable.c_str());
}

void PufferMake::Maker::Build() {
    Compile();
    auto build_type = m_config.BuildType();
    if (build_type == "executable") {
        LinkExecutable();
    } else if (build_type == "shared") {

    } else if (build_type == "static") {

    }
    LinkExecutable();
}

void PufferMake::Maker::BuildAndRun() {
    Build();
    Run();
}

void PufferMake::Maker::LoadFilters(std::vector<std::string>& filters, FileList& files) {
    for (auto filter : filters) {
        const char* filter_str = filter.c_str();
        files.AddFilterExtension(std::wstring(filter_str,filter_str + filter.length()));
    }
}

std::string PufferMake::Maker::RunProcess(const char* command) {
    std::array<char, 255> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string PufferMake::Maker::GetFileNameWithoutExtension(std::string path) {
    auto filenamepos = path.find_last_of("/");
    std::string name_wext = path.substr(filenamepos + 1);
    auto extpos = name_wext.find(".");
    return name_wext.substr(0, extpos);
}

void PufferMake::Maker::PreProcessFile(std::wstring current_name) {
    std::string converted_str(current_name.begin(), current_name.end());
    std::cout << "Starting to prepare preprocessing of " << converted_str << std::endl; 
    std::stringstream command;
    command << "g++ -E " << converted_str;
        
    std::string result = RunProcess(command.str().data());
    std::string filename = "preprocessed/";
    filename += GetFileNameWithoutExtension(converted_str);
    filename += ".i";
    std::ofstream outputfile(filename, std::ios::trunc);
    outputfile << result << std::endl;
    std::cout << "Preprocessing of " << converted_str 
        << " has finished." << std::endl << result << std::endl;
}

void PufferMake::Maker::CompileFile(std::wstring current_name) {
    std::string converted(current_name.begin(), current_name.end());
    std::cout << "Starting compilation of " 
        << COLOUR_GREEN_F << converted 
        << COLOUR_RESET << std::endl;
    std::stringstream command;
    command << "g++ ";
    auto debug = m_config.Debug();
    if (debug.length() != 0) {
        command << '-' << debug << ' ';
    }

    command << "-c ";
    command << '\"' << converted << '\"' << ' ';
    auto includes = m_config.IncludeDirectories();
    for (auto str : includes) {
        command << "-I\"" << str << "\" ";
    }

    auto version = m_config.CppVersion();
    if (version.length() != 0) {
        command << "-std=" << version << ' ';
    }

    auto optimization = m_config.Optimization();
    if (optimization.length() != 0) {
        command << '-' << optimization;
    }

    auto warnings = m_config.Warnings();
    if (warnings.length() != 0) {
        if (warnings == "disabled") {
            command << " -w";
        }
        if (warnings == "all") {
            command << " -Wall";
        }
        if (warnings == "extra") {
            command << " -Wextra";
        }
    }
    std::string result = RunProcess(command.str().data());
    std::cout << "Compilation of " << converted 
        << " has finished." << std::endl << result;
}