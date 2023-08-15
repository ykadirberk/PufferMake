#include "Maker.h"

PufferMake::Maker::Maker() : m_source_files(),
                             m_header_files(),
                             m_object_files(),
                             m_preprocessed_files(),
                             m_staticlib_files(),
                             m_dynamiclib_files() {

}

PufferMake::Maker::~Maker() {

}

void PufferMake::Maker::Initialize() {
    Configuration configuration;
    configuration.Initialize();

    auto source_file_filters = configuration.SourceFileFilters();
    auto header_file_filters = configuration.HeaderFileFilters();
    auto object_file_filters = configuration.HeaderFileFilters();
    auto preprocessed_file_filters = configuration.HeaderFileFilters();
    auto staticlib_file_filters = configuration.HeaderFileFilters();
    auto dynamiclib_file_filters = configuration.HeaderFileFilters();

    LoadFilters(source_file_filters,        m_source_files);
    LoadFilters(header_file_filters,        m_header_files);
    LoadFilters(object_file_filters,        m_object_files);
    LoadFilters(preprocessed_file_filters,  m_preprocessed_files);
    LoadFilters(staticlib_file_filters,     m_staticlib_files);
    LoadFilters(dynamiclib_file_filters,    m_dynamiclib_files);

}

void PufferMake::Maker::LoadFiles() {
    auto cwd = std::filesystem::current_path();

    for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(cwd)) {
        if (dir_entry.is_directory()) {
            continue;
        }

        auto current_path = dir_entry.path().wstring();

        m_source_files.         TryAddFile(current_path);
        m_header_files.         TryAddFile(current_path);
        m_object_files.         TryAddFile(current_path);
        m_preprocessed_files.   TryAddFile(current_path);
        m_staticlib_files.      TryAddFile(current_path);
        m_dynamiclib_files.     TryAddFile(current_path);
    }
}

void PufferMake::Maker::PreProcess() {
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

}

void PufferMake::Maker::Compile() {

}

void PufferMake::Maker::Link() {

}

void PufferMake::Maker::Run() {
    std::system("./target/app &");
}

void PufferMake::Maker::Build() {
    Compile();
    Link();
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

    std::stringstream command;
    command << "g++ -E " << converted_str;
        
    std::string result = RunProcess(command.str().data());
    std::string filename = "preprocessed/";
    filename += GetFileNameWithoutExtension(converted_str);
    filename += ".i";
    std::ofstream outputfile(filename, std::ios::trunc);
    outputfile << result << std::endl;
}