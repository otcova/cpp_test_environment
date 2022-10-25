#include <string>

#if defined(WIN32)
#include <windows.h>

/// Windows doesn't support UTF8 characters the macro 'ENABLE_UTF8_OUTPUT()'
/// will configure console if necessary.
#define ENABLE_UTF8_OUTPUT() SetConsoleOutputCP(CP_UTF8)
#else

/// Windows doesn't support UTF8 characters the macro 'ENABLE_UTF8_OUTPUT()'
/// will configure console if necessary.
#define ENABLE_UTF8_OUTPUT()
#endif

/**
 * @brief
 * Executes a command synchronous and redirects std::out, std::in, std::err
 * into strings.
 * On Windows it will use the powershell.
 *
 * @param command Command and arguments to be executed synchronous.
 * @param input Text to be piped to the standard output of the command.
 * @return The standard output of the command.
 *
 * @throw
 * If the command returns an error code, the std::err will be thrown as a string.
 */
std::string execute_command(const std::string& command, const std::string& input = "");
