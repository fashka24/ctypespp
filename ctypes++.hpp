#ifndef _CTYPES_PP_H
#define _CTYPES_PP_H

#include <string>
#include <stdexcept>
#include <functional>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace ctypes
{

    class DynamicLibrary
    {
    public:
        DynamicLibrary(const std::string &libraryPath)
        {
#ifdef _WIN32
            handle = LoadLibrary(libraryPath.c_str());
            if (!handle)
            {
                throw std::runtime_error("[CTYPES] Cannot load library: " + libraryPath);
            }
#else
            handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
            if (!handle)
            {
                throw std::runtime_error("[CTYPES] Cannot load library: " + std::string(dlerror()));
            }
#endif
        }

        ~DynamicLibrary()
        {
#ifdef _WIN32
            FreeLibrary((HMODULE)handle);
#else
            dlclose(handle);
#endif
        }

        template <typename Ret, typename... Args>
        std::function<Ret(Args...)> getf(const std::string &functionName)
        {
            FARPROC func = nullptr;
#ifdef _WIN32
            func = GetProcAddress((HMODULE)handle, functionName.c_str());
            if (!func)
            {
                throw std::runtime_error("[CTYPES] Cannot load symbol '" + functionName + "'");
            }
#else
            func = dlsym(handle, functionName.c_str());
            const char *dlsym_error = dlerror();
            if (dlsym_error)
            {
                throw std::runtime_error("[CTYPES] Cannot load symbol '" + functionName + "': " + std::string(dlsym_error));
            }
#endif

            return std::function<Ret(Args...)>(reinterpret_cast<Ret(*)(Args...)>(func));
        }

    private:
        void *handle;
    };

}

#endif // _CTYPES_PP_H