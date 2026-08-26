#include <iostream>
#include <string>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    std::string procName = "python3";
    std::string procCommand = "python3 src/other/test_exit.py";
    int limit = 3;
    Process root(procName, procCommand, limit);
    int stat = root.run();
    std::cout << "Process exited with: " << stat << "\n";
}
