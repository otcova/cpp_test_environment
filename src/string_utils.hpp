#include <fstream>
#include <string>

/// similar of std::getline, but it reads a block of text separated by empty lines.
bool read_until_empty_line(std::ifstream& input, std::string& block);

/// Equivalent of str * repeat on python
std::string repeat_string(const std::string& str, int repeat);

/// Replaces all ocurramces of 'from' for 'to' on 'str'
void replaceAll(std::string& str, const std::string& from, const std::string& to);

/// Returns the length of the longest line.
int max_line_length(const std::string& lines);

/**
 * @param lines string containing lines seperated by <LF> or <CRLF>.
 * @param final_length 
 * if a line of is smaller than final_length, it will be padded with spaces.
 * @param start_with string to be inserted before every line.
 * @param end_with string to be inserted after every line.
 * @return for each line on lines: start_with + line + padding_spaces + end_with
 */
std::string pad_lines(
    const std::string& lines,
    int final_length,
    const std::string& start_with = "",
    const std::string& end_with = "");
