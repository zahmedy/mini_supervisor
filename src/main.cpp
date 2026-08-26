#include <iostream>
#include <string>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    std::string procName = "sleep";
    std::string procCommand = "sleep 142";
    int limit = 3;
    Process root(procName, procCommand, limit);
    int stat = root.start();
    int waited = root.wait();
    if (stat < 0)
    {
        std::cout << "Process: " << root.get_name() << " failed to start." << "\n";
        return stat;
    }
    if (waited < 0)
    {
        if (waited == 9)
        {
            std::cout << "Process: " << root.get_name() << " got killed." << "\n";
        }
        else if (waited == 15)
        {
            std::cout << "Process: " << root.get_name() << " got terminated." << "\n";
        }
        else if (waited == 2)
        {
            std::cout << "Process: " << root.get_name() << " got interrupted." << "\n";
        }
        else if (waited == 6)
        {
            std::cout << "Process: " << root.get_name() << " got aborted." << "\n";
        }
        else
            std::cout << "Process: " << root.get_name() << " returned status." << waited << "\n";
    }

    return stat;
}
