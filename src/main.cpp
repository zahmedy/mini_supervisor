#include <iostream>
#include <string>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    std::string procName = "sleep";
    std::string procCommand = "sleep 30";
    int limit = 3;
    Process root(procName, procCommand, limit);
    int stat = root.start();
    if (stat < 0)
    {
        std::cout << "Process: " << root.get_name() << " failed to run." << "\n";
        return stat;
    }
    std::cout << "Process: " << root.get_name() << " ran." << "\n";
    return stat;
}
