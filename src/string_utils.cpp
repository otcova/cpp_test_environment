#include "string_utils.h"
#include <iostream>

using namespace std;

bool read_until_empty_line(ifstream& input, string& block)
{
    block = "";
    string line;
    while (getline(input, line) and (line != "" and line != "\r" or block == "")) {
        if (line != "" and line != "\r")
            block += line + "\n";
    }
    return block != "";
}

string pad_lines(const string& text, int final_length, const string& start_with, const string& end_with)
{
    int line_len = 0;
    string padded = "";

    for (int i = 0; i < text.length(); ++i) {
        // Insert Start Line
        if (i == 0 or text[i - 1] == '\n') {
            padded += start_with;
        }

        // Skip color code (color example: "\033[1;31m")
        if (text[i] == '\033') {
            while (text[i] != 'm') {
                padded += text[i];
                ++i;
            }
            padded += text[i];
        }
        // Insert Pad and End Line
        else if (text[i] == '\n') {
            int pad = final_length - line_len;
            for (int j = 0; j < pad; ++j)
                padded += ' ';
            padded += end_with + '\n';
            line_len = 0;
        }
        // Copy chars from input text
        else if (text[i] != '\r') {
            ++line_len;
            padded += text[i];
        }
    }

    // if last line doesn't end with '\n'
    if (text.length() != 0 and line_len != 0) {
        int pad = final_length - line_len;
        padded += "\033[1;31m⤶\033[0m";
        for (int j = 1; j < pad; ++j)
            padded += ' ';
        padded += end_with;
        padded += "\n";
    }

    return padded;
}

string repeat_string(const string& str, int repeat)
{
    string r = "";
    for (int i = 0; i < repeat; ++i)
        r += str;
    return r;
}

int max_line_length(const string& lines)
{
    int max_len = 0;
    int line_len = 0;
    for (int i = 0; i < lines.length(); ++i) {
        if (lines[i] == '\033') {
            // Skip color code (color example: "\033[1;31m")
            while (lines[i] != 'm')
                ++i;
        } else if (lines[i] == '\n') {
            max_len = max(max_len, line_len);
            line_len = 0;
        } else if (lines[i] != '\r') {
            ++line_len;
        }
    }
    return max(max_len, line_len);
}

void replaceAll(string& str, const string& from, const string& to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}