#include "Bindings.h"
#include <exception>

//[[EXPORT]]
void setupCallbacks(
    void (*logErrorCallback)(char* message),
    void (*logMessageCallback)(char* message)
    )
{
    try
    {
        logError = logErrorCallback;
        logMessage = logMessageCallback;
    }
    catch (const std::exception& e)
    {
        logError(const_cast<char*>(e.what()));
    }
}