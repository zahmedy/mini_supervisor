#pragma once
#include "./Process.hpp"

class Supervisor
{
private:
    Process process_;

public:
    // Constructor
    Supervisor(Process process);

    Process get_process();
    void add();
    int run();
};