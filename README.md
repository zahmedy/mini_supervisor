#MINI SUPERVISOR
_Start, monitor, restart, and stop Linux processes._

                    minisupervisor
                         │
             ┌───────────┼───────────┐
             ↓           ↓           ↓
          server       worker      logger
             │           │           │
          PID 1234     PID 1235    PID 1236
             │           │           │
             └───────────┼───────────┘
                         ↓
                    health monitor
                         │
                  process dies?
                         │
                         ↓
                       restart
