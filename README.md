# libbla
A library for Time Measurement and Control Blocks for Bare-Metal C++ Applications

This library combines timing specification and a concept for time annotation and control blocks in C++. Our proposed blocks can be used to
measure and profile software block execution time. Furthermore, it can be used to control and enforce the
software time behavior at run-time. After the application of these time blocks a trace based verification against
the block based timing specification can be performed to obtain evidence on the correct implementation and
usage of the time blocks on the target platform.