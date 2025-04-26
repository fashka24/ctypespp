#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
    int add(int a, int b) {
        return a + b;
    }

    int subtract(int a, int b) {
        return a - b;
    }

    void greet(const char* name) {
        std::cout << "Hello, " << name << "!" << std::endl;
    }
#ifdef  __cplusplus
}
#endif