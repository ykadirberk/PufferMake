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

}

void PufferMake::Maker::Compile() {

}

void PufferMake::Maker::Link() {

}

void PufferMake::Maker::Run() {

}

void PufferMake::Maker::Build() {

}

void PufferMake::Maker::BuildAndRun() {

}

void PufferMake::Maker::LoadFilters(std::vector<std::string>& filters, FileList& files) {
    for (auto filter : filters) {
        const char* filter_str = filter.c_str();
        files.AddFilterExtension(std::wstring(filter_str,filter_str + filter.length()));
    }
}