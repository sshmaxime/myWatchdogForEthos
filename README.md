# myWatchdogForEthos 1.3.0

## Introduction

This script wait 10 minutes after that the system booted and check every minute if one of your GPU crashed. If that's the case it reboot your rig.


## Getting Started

In order for you to compile the program and get the executable follow these steps :

- Clone this repository

- ```mkdir build```

- ```cd build && cmake ../```

- ```make```

Now copy this file at /home/ethos and call it from the ```custom.sh``` file.

You should see that in your ```custom.sh``` file:

```
#!/bin/bash
# /home/ethos/custom.sh
# This file is where you should put any custom scripting you would like to run. 
# It will run once, after Xorg (Graphical interface) starts up, any commands which you absolutely have to run before xorg should be located in rc.local befo$
# All scripting in this file should be before the "exit 0" as well.  Preface any commands which require 'root' privileges with the "sudo" command
# Examples script running as user ethos: 
# my_command --my flags
# Example of a php script running as user root:
# sudo php /path/to/my/script.php

sudo ./myWatchdog &

exit 0
```

Enjoy !
