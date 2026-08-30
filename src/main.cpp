#include <iostream>
#include <string>
#include <unistd.h>
#include "../include/mini_supervisor/Process.hpp"

int main()
{
    Process process("test", "/tmp/Parent", 3);

    process.start();

    std::cout << "PID: " << process.get_pid() << "\n";

    sleep(2);

    process.stop();

    process.wait();

    return 0;
}
