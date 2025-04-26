# builder of dev.cpp, testlib.cpp

import os

target = "dev.cpp"
include = "."

command = f"g++ -w -O3 {target} -o dev -I{include}"
os.system(command)

target = "testlib.cpp"
include = "."

command = f"g++ -shared {target} -o testlib.dll -I{include}"
# command = f"g++ -shared {target} -o testlib.so -I{include} -fPIC" LINUX
os.system(command)