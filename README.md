CTypes++ - simple library for loading DLL/SO files in C++

example:
```c++
    #include <iostream>
    #include <ctypes++.hpp>

    int main(int argc, char const *argv[])
    {
        ctypes::DynamicLibrary testlib("testlib.dll");
        // LINUX:
        // ctypes::DynamicLibrary testlib("testlib.so");

        auto add = testlib.getf<int, int, int>("add");
        auto subtract = testlib.getf<int, int, int>("subtract");
        auto greet = testlib.getf<void, const char*>("greet");

        std::cout << add(1, 2) << "\n";
        std::cout << subtract(1, 2) << "\n";
        greet("Steve");

        return 0;
    }
```

syntax DynamicLibrary.getf:
```c++
    // Ret - return type, Args - arguments type
    // functionName - name of getting function

    template <typename Ret, typename... Args>
    std::function<Ret(Args...)> getf(const std::string &functionName)
```