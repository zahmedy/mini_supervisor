#include "../include/mini_supervisor/Supervisor.hpp"
#include <iostream>

Supervisor::Supervisor(Process process, int limit) : limit_(limit)
{
    processes_.push_back(std::move(process));
};

std::vector<Process> Supervisor::get_processes()
{
    return processes_;
}

// ADD
int Supervisor::add(Process process)
{
    processes_.push_back(std::move(process));
}

// RUN
int Supervisor::run()
{
    for (Process &process : processes_)
    {

        int start_rc = process.start();

        if (start_rc < 0)
        {
            std::cout << "Error: failed to start " << process.get_name() << "\n";
            return -1;
        }

        int wait_rc = process.wait();
        int restartCount = 0;

        // keep starting the process based on set limit
        while (restartCount < limit_)
        {
            if (wait_rc == -100)
            {
                std::cout << "waitpid function failed, exiting...\n";
                return -1;
            }
            else if (wait_rc < 0)
            {
                std::cout << "process got signal from kernel, restarting...\n";
                start_rc = process.start();
                restartCount += 1;

                if (start_rc < 0)
                {
                    std::cout << "failed to start the process, exiting\n";
                    return -1;
                }

                wait_rc = process.wait();
            }
            else
            {
                // Process exited normally, we're done!
                break;
            }
        }
        return wait_rc;
    }
}
// END RUN

// STOP_ALL
int Supervisor::stop_all()
{
    for (Process &process : processes_)
    {
        int rc = process.stop();

        if (rc != 0)
        {
            std::cout << "Err: Failed to stop process " << process.get_name() << "\n";
            return -1;
        }
    }

    return 0;
}
// END STOP_ALL
