*This project has been created as part of the 42 curriculum by tsordo-o.*

# Codexion

## Description
This is a C/pthreads simulation of `n` coders that are sitting in a circular inclusive co-working hub. Said coders must complete a series of actions in order and not simultaneously: `compile, debug and refactor`.
In order to compile, a `coder` must hold exactly `two USB dongles`. There's `one dongle` per coder and each of them sits between each pair of coders.
A `dongle` can't be held by two `coders` at the same time, and, immediately after being used, the remain unusable for a period of time defined by `cooldown`.
The simulation `stops` either when all coders finish compiling the required `number of compilations` or when at least one of them `burns out`.
Coders `burn out` when they haven't be able to compile for a specific period of time defined by `burnout`.
The main goal of this simulation is to complete the required number of compilations while `avoiding` coders burnout, without letting them communicate with each other, or access any information directly from one another.

## Instructions

### Makefile
A Makefile has been provided to simplify execution including the following commands:
```
make
```
Compiles every `.c` source file `.0` objects files, and links them into the executable `codexion`.

```
make clean
```
Remove all object files from `Objects/` and the project root.

```
make fclean
```
Runs `make clean` and also removes the `codexion` executable.

```
make re
```
Runs `make fclean` and rebuilds the project from scratch.

### Usage

Run the program as:

```
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```
Example:
```
./codexion 200 1600 200 200 200 200 10 edf
```

### Warning
```
Program will return an `Error` if any of the numeric arguments is not entirely numeric, if they are <= 0, if they exceed the limits defined by `INT_MAX` and `INT_MIN`, or if the `scheduler` is not either `fifo` or `edf` (case sensitive).
```

## Resources
https://hpc-tutorials.llnl.gov/posix/
https://pages.cs.wisc.edu/~remzi/OSTEP/threads-cv.pdf
https://en.wikipedia.org/wiki/Dining_philosophers_problem
https://pubs.opengroup.org/onlinepubs/009604599/functions/pthread_cond_timedwait.html   
https://en.wikipedia.org/wiki/Priority_queue
https://www.geeksforgeeks.org/c/c-program-to-implement-priority-queue/
https://www.geeksforgeeks.org/c/function-pointer-in-c/
https://medium.com/@alexey.medvecky/mastering-heaps-from-c-simplicity-to-custom-c-implementation-that-powers-efficient-algorithms-27ff2938ecaa
https://jraleman.medium.com/c-programming-language-passing-a-function-as-a-parameter-90d52fe842ea

### AI Usage
Claude.ai and copilot were used mainly to help with the project's design optimization and to better detect flaws and bugs in it, `no code was requested and/or provided`.

## Blocking cases handled

- __Deadlock prevention__: `Circular Wait` Coffman's condition was avoided completely by never creating a scenario in which a thread waits for a resource, that a different thread holds while waiting for another resource a third thread is currently holding. The only thread that waits for a mutex to be unlocked, while holding another one, is the `monitor thread`, and that is, only when holding the `shared_mutex` and `burnout check` is affirmative, so it may wait for the `stdout_mutex` to be unlock in order to print the `burnout message`. `Coder threads` never need to hold two mutexes at the same time, so a `Circular Wait` is, therefore, `impossible`.

- __Starvation prevention__: two mechanisms were implemented for this matter and they are better explained using this example
```
We have n coders but we will focus only on coder 1 and 2.
Coder 1 has higher priority than Coder 2, either because it made the request before Coder 2 or because it's closer to burnout time.
Coder 1 needs dongle 1 and 0 to compile but the latter is unavailable.
Coder 2 needs dongle 1 and 2, and they are both available.
Coder 2 is able to compile but letting it do so could result in Coder 1 burning out.
To prevent this, when the monitor evaluates Coder 1 request, it marks dongle 0 and 1 as 'requested'. This results in Coder 2 request being evaluated as impossible.
This would cause a new problem. Coder 2 could burnout while waiting for Coder 1 to compile and then wait for dongle 1 cooldown, even though both of it's required dongles are available.
To solve this, when a dongle is marked as 'requested', the requester records it's burnout time on it as well, so that before the monitor marks Coder 2 request as impossible, it considers the ms left to said timestamp, checking if ms_left > COMPILATION_TIME + DONGLE_COOLDOWN. If TRUE, that means Coder 2 could be let go without making Coder 1 burnout, therefore, Coder 2 request is marked as valid.
```

- __Cooldown handling__: every time a coder finishes a successful compilation it updates the dongles cooldown it used, by recording an `absolute time timestamp`. These timestamps are made considering the `current time` at the moment of the update, using `gettimeofday()`, and adding `COOLDOWN_TIME` to it. Then, when the `monitor` evaluates a coders request, it checks if `current time` is passed the dongles `cooldown timestamp`. This check will determine if the dongle is still in cooldown or not.

- __Precise burnout detection__: this works similar to cooldown handling. Each coders properties struct includes an `absolute time timestamp` related to its burnout time. These timestamps are first set at the beginning of the simulation, when initializing coder threads, and updated by the `monitor` each time it gives a coder permission to continue working, in the same way as cooldown ones (current time + BURNOUT_TIME).
The `monitor` is in charge of checking each coders burnout time each time it starts its routine. To guarantee burnout detection delay as little as possible, when putting the `monitor` to "sleep" at the end of its routine, the `closest` burnout time is taken in consideration as deadline after which the monitor would be "woken up". 

- __Log serialization__: using gettimeofday(), a timestamp is recorded at the beggining of the simulation as `start_time`. `time_since_start()` is used to calculate the time (in ms) that has passed since start_time, and `log_event()` is in charge to lock the `stdout dedicated mutex`, call time_since_start(), print the desired message as `"<ms since start> <coder id> <event>\n"`, and finish with said mutex unlock. A dedicated mutex is used so that two different messages never interleave on a single line.

## Thread synchronizaction mechanisms

- __Mutexes__: two mutexes were established for the whole simulation, `shared_mutex` and `mutex_stdout`.

  - __shared_mutex__: it helps to prevent data corruption when both the monitor and coders perform read/write processes on the requests queue, and on each coders stop and has_permission flags.
  - __mutex_stdout__: it is used to guarantee two different messages never interleave on a single line.

- __Condition Variables__: a dedicated condition variable is at each thread disposal, so that they can be either suspended or signal when necessary.
  
  - __monitor thread__: it is suspended at the end of its cycled routine, and woken up only when at least one of the following situations occur: a `coder` sends a `new request`; a `dongle` has finished its `cooldown period`; a coders `burnout time` has been reached.

  - __coder threads__: they are suspended while waiting for either their `stop` or `has_permission` flags to be set, after making a new request. Said suspension is wrapped in a loop in order to prevent `spurious wakeups`. They are woken up, when either the monitor has detected a `burnout` or when it scanned a coders `request` as valid.
