#include <iostream>
#include <string>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    std::string procName = "root";
    std::string procCommand = "init .";
    int limit = 3;
    Process root(procName, procCommand, limit);
    std::cout << "Process: " << root.name << " Started." << "\n";
}
