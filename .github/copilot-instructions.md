# Copilot instructions

## Build and run

- Build with `make` (`cc` with `-Wall -Wextra -Werror -pthread -g`).
- Rebuild from scratch with `make re`; remove objects with `make clean`, or objects and the executable with `make fclean`.
- There is no automated test or lint target. Run one simulation as a smoke test with:
  `make && ./codexion 5 800 200 200 200 50 3 fifo`
- Arguments are: coder count, burnout time, compile time, debug time, refactor time, dongle cooldown, required compiles, and scheduler (`fifo` or `edf`).

## Architecture

This is a C/pthreads simulation of coders sharing dongles arranged in a ring. `main.c` parses the configuration, initializes shared state, starts the monitor and coder threads, joins them, and cleans up.

`codexion.h` defines the shared configuration and state structures. `startup_utils.c` allocates and initializes the monitor's coder, dongle, and request-heap state. Each coder runs `threads/coder/coder_routine.c`: it submits a request, waits for the monitor's permission, uses its two neighboring dongles to compile, then debugs and refactors.

The monitor in `threads/monitor/monitor_routine.c` owns request scheduling and burnout/completion checks. Requests live in the binary min-heap under `heap/`; `heap/utils/init_heap.c` selects the comparator: FIFO compares request timestamps, while EDF compares the requesting coder's burnout deadline. `threads/monitor/monitor_utils/handle_request.c` checks dongle availability and cooldowns, reserves both dongles, and wakes the selected coder.

Coder and monitor state, including the heap and dongles, is coordinated with `shared_mutex`; per-coder and monitor condition variables handle wakeups. `mutex_stdout` serializes event output. Time helpers are in `time_utils.c`; resource teardown is handled by `finish_simulation.c` and `free_all.c`.

## Repository conventions

- Shared types, enums, and function declarations belong in the root `codexion.h`; implementation is split between root-level utilities and the `heap/` and `threads/` modules.
- The Makefile explicitly enumerates every source file in `SRCS`. Add new implementation files there or they will not be compiled by `make`.
- Heap operations use one-based request indices (`requests[1..size]`), and the configured comparator determines heap priority. Preserve this indexing and comparator-based ordering when changing heap behavior.
- The ring assigns coder `i` dongle `i` and the preceding dongle, with coder `0` wrapping to the final dongle. Keep this adjacency consistent in scheduling and dongle updates.
