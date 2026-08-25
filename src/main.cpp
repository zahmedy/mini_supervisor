#include <iostream>
#include <string>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    std::string procName = "exit";
    std::string procCommand = "exit 42";
    int limit = 3;
    Process root(procName, procCommand, limit);
    int stat = root.start();
    int waited = root.wait();
    if (stat < 0)
    {
        std::cout << "Process: " << root.get_name() << " failed to run." << "\n";
        std::cout << "Process's wait status: " << waited << "\n";
        return stat;
    }
    std::cout << "Process: " << root.get_name() << " ran." << "\n";
    return stat;
}
