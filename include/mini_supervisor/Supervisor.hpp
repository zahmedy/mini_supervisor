#pragma once
#include "./Process.hpp"

class Supervisor
{
private:
public:
    // Constructor
    Supervisor(Process process);

    void add();
    int run();
};