#include "../include/mini_supervisor/Supervisor.hpp"
#include <iostream>

Supervisor::Supervisor(Process process) : process_(process) {};

Process Supervisor::get_process()
{
    return process_;
}

int Supervisor::run()
{
    int start_rc = process_.start();

    if (start_rc < 0)
    {
        std::cout << "Error: failed to start " << process_.get_name() << "\n";
        return -1;
    }

    int wait_rc = process_.wait();
    int restartCount = 0;

    // keep starting the process based on set limit
    while (restartCount < process_.get_limit())
    {
        if (wait_rc == -100)
        {
            std::cout << "waitpid function failed, exiting...\n";
            return -1;
        }
        else if (wait_rc < 0)
        {
            std::cout << "process got signal from kernel, restarting...\n";
            start_rc = process_.start();

            if (start_rc < 0)
            {
                std::cout << "failed to start the process, exiting\n";
                return -1;
            }
        }
        else
        {
            // Process exited normally, we're done!
            break;
        }
    }
    return wait_rc;
}
