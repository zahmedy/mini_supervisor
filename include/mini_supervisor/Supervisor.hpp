#pragma once

#include "./Process.hpp"
#include <vector>

class Supervisor
{
private:
    std::vector<Process> processes_;
    int limit_;

public:
    // Constructor
    Supervisor(Process process, int limit);

    // Steers
    void set_limit(int limit);

    // Getters
    std::vector<Process> get_processes();
    int get_limit() const;
    int add(Process process);
    int run();
    int stop_all();
};