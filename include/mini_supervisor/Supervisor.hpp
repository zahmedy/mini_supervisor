#pragma once
#include "./Process.hpp"

class Supervisor
{
private:
    Process process_;
    int limit_;

public:
    // Constructor
    Supervisor(Process process, int limit);

    // Steers
    void set_limit(int limit);

    // Getters
    Process get_process();
    int get_limit() const;
    void add();
    int run();
};