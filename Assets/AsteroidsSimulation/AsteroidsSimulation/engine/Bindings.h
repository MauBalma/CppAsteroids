#pragma once

#ifdef DLL_EXPORT
#define DLL extern "C" __declspec(dllexport)
#else
#define DLL extern "C" __declspec(dllimport)
#endif

inline void (*logError)(char* message);
inline void (*logMessage)(char* message);


/*[[EXPORT]]*/ DLL void setupCallbacks(
    void (*logErrorCallback)(char* message),
    void (*logMessageCallback)(char* message)
    );