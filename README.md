# symon
Tiny Command Line Interface Remote System Monitor.

## How to use

Start server:
```console
lzcdr@DESKTOP-AEFDRRD:~$ symon_server 127.0.0.1 8123
```

Request system parameters:
```console
lzcdr@DESKTOP-AEFDRRD:~$ symon_client 127.0.0.1 8123
cpu utilization:  8.40673%
total ram:        8358567936
free ram:         1262432256
total disk space: 253966151680
free disk space:  104380334080
```

## How to build

See src/readme.1st
