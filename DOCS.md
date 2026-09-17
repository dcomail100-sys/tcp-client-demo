# PulseNet

Simple TCP client written in C for learning low-level networking.

## Features
- TCP_NODELAY (disable Nagle algorithm)
- Non-blocking socket
- poll() for I/O readiness
- Send a short message
- Receive with timeout (2 seconds)
- Clean shutdown

## Build
```bash
gcc main.c -o client