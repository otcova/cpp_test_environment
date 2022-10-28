#include "string_utils.h"

#include <fstream>
#include <iostream>
#include <atomic>

using namespace std;

atomic<int> id { 0 };

string system_redirect_output(const string& command)
{
    string output_path = ".system_redirected_output_" + to_string(++id);
    string cmd = command + " > " + output_path + " 2>&1";
    int error = system(cmd.c_str());
    ifstream file(output_path, ios::in | ios::binary);
    string result;
    if (file) {
        int c;
        while ((c = file.get()) != EOF)
            result.push_back(c);
        file.close();
    }
    remove(output_path.c_str());

    if (error != 0)
        throw result;
    return result;
}

#if defined(WIN32)
string execute_command(const string& command, const string& input)
{
    string output;
    uint32_t return_code = 0;

    string command_with_input = "PowerShell -Command \"echo \\\"" + input + "\\\" | " + command + "\"";
    replaceAll(command_with_input, "\r", "");
    replaceAll(command_with_input, "\n", "`n");

    output = system_redirect_output(command_with_input);

    if (return_code != 0) {
        throw output;
    }

    return output;
}

#else

string execute_command(const string& command, const string& input)
{
    string output;
    uint32_t return_code = 0;

    string command_with_input = "echo \"" + input + "\" | " + command;
    replaceAll(command_with_input, "\r", "");
    replaceAll(command_with_input, "\n", "\\n");

    output = system_redirect_output(command_with_input);

    if (return_code != 0) {
        throw output;
    }

    return output;
}

#endif