#include <iostream>
#include <string>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    std::string procName = "cash";
    std::string procCommand = "sleep 30";
    int limit = 3;
    Process root(procName, procCommand, limit);
    int stat = root.run();
    std::cout << "Process exited with: " << stat << "\n";
}
