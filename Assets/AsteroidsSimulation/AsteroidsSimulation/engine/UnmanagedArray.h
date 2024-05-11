#pragma once

struct UnmanagedArray
{
    void* ptr;
    size_t length;
    
    size_t sizeOf;
    size_t alignOf;
};
