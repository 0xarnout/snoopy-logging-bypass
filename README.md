## Quick start
Compile with `gcc bypass.so -shared -fPIC -ldl -o bypass.so`. Then run `LD_PRELOAD=$PWD/bypass.so bash`. Any commands executed in this shell will not be logged by snoopy.

## How it works
Snoopy works by preloading the libsnoopy.so library, which overrides the execv and execve functions provided by libc in order to log commands. By loading this library *before* snoopy with the LD_PRELOAD environment variable, bash (or any other program) will use the execv and execve functions provided by bypass.so, and those functions will provide direct access to the libc execv/execve, bypassing logging by snoopy.

## Credits
This tool is based [this](https://blog.rchapman.org/posts/Bypassing_snoopy_logging/) blog by Ryan A. Chapman.
