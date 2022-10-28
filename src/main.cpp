#include "colors.h"
#include "string_system.h"
#include "string_utils.h"

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

using namespace std;

mutex cout_mutex;

void run_test_case(string test_case_input)
{
    string output;
    try {
        output = execute_command("./.exe", test_case_input);
    } catch (const string& error_msg) {
        output = pad_lines(error_msg, 0, "\033[1;31m", "\033[0m");
    }
    int width = max(0, max(max_line_length(test_case_input), max_line_length(output)));

	cout_mutex.lock();
    cout << "╔" << repeat_string("═", width + 2) << "╗" << endl;
    cout << pad_lines(test_case_input, width, "║ ", " ║");
    cout << "╟" << repeat_string("─", width + 2) << "╢" << endl;
    cout << pad_lines(output, width, "║ ", " ║");
    cout << "╚" << repeat_string("═", width + 2) << "╝" << endl;
    cout_mutex.unlock();
}

int main()
{
    ENABLE_UTF8_OUTPUT();

    try {
        execute_command("g++ -fdiagnostics-color=always -ansi -Wall -O2 -DNDEBUG"
                      " -Wextra -Werror -Wno-uninitialized -Wno-sign-compare"
                      "-Wshadow program.cc -o .exe");
    } catch (const string& compilation_error) {
        cout << COLOR_RED "   ---   Compilation Error   ---" DEFAULT_COLOR << endl;
        cout << compilation_error;
        return 1;
    }

    vector<thread> threads;
    
    ifstream input;
    input.open("input");
    
    string test_case_input;
    while (read_until_empty_line(input, test_case_input)) {
        threads.push_back(thread(run_test_case, test_case_input));
    }
    
    for (thread& thread : threads) {
        thread.join();
    }

    remove(".exe");
}
