#include <iostream>
#include <string>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    std::string procName = "sleep";
    std::string procCommand = "sleep 60";
    int limit = 3;
    Process root(procName, procCommand, limit);
    root.start();
    std::cout << "Process: " << root.get_name() << " Started." << "\n";
}
