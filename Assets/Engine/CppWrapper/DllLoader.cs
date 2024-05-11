using System;
using System.Runtime.InteropServices;

public static class DllLoader
{
    [DllImport("kernel32")]
    private static extern IntPtr LoadLibrary(string path);
 
    [DllImport("kernel32")]
    private static extern IntPtr GetProcAddress(IntPtr libraryHandle, string symbolName);
 
    [DllImport("kernel32")]
    private static extern bool FreeLibrary(IntPtr libraryHandle);
 
    public static IntPtr OpenLibrary(string path)
    {
        var handle = LoadLibrary(path);
        
        if (handle == IntPtr.Zero) 
            throw new Exception("Couldn't open native library: " + path);
        
        return handle;
    }
 
    public static void CloseLibrary(IntPtr libraryHandle)
    {
        FreeLibrary(libraryHandle);
    }
 
    public static T GetDelegate<T>(IntPtr libraryHandle, string functionName) where T : class
    {
        var symbol = GetProcAddress(libraryHandle, functionName);
        
        if (symbol == IntPtr.Zero)
            throw new Exception("Couldn't get function: " + functionName);
        
        return Marshal.GetDelegateForFunctionPointer(symbol, typeof(T)) as T;
    }
}
