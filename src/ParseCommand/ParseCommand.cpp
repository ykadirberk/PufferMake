#include "ParseCommand.h"

PufferMake::ParseCommand::ParseCommand(int argument_count, char* arguments[]) 
    : m_arguments(), m_invalid_message() 
{
    if (argument_count < 2) {
        m_valid = false;
        m_invalid_message = "insufficient argument count.";
        return;
    }
    for (int i = 1; i < argument_count; i++) {
        m_arguments.push_back(arguments[i]);
    }
}
    
PufferMake::ParseCommand::~ParseCommand() {

}

bool PufferMake::ParseCommand::IsValid() {
    return m_valid;
}

std::string PufferMake::ParseCommand::ErrorMessage() {
    return m_invalid_message;
}

std::string PufferMake::ParseCommand::GetCommand() {
    return m_arguments[0];
}