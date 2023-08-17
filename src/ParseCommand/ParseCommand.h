#include <vector>
#include <string>


namespace PufferMake {
    class ParseCommand{
        public:
            ParseCommand(int argument_count, char* arguments[]);
            ~ParseCommand();

            bool IsValid();
            std::string ErrorMessage();

            std::string GetCommand();
            
        private:
            std::vector<std::string> m_arguments;
            std::string m_invalid_message;
            bool m_valid = true;
    };
       
}
