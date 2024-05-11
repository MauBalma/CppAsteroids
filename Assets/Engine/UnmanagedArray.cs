using System;
using Unity.Collections;
using Unity.Collections.LowLevel.Unsafe;
using UnityEngine.Assertions;

namespace Engine
{
    public unsafe struct UnmanagedArray
    {
        public readonly void* ptr;
        public readonly ulong length;
        public readonly ulong sizeOf;
        public readonly ulong alignOf;

        public T Read<T>(int index) where T : unmanaged
        {
            Assert.AreEqual(UnsafeUtility.SizeOf<T>(), (int)sizeOf);
            Assert.AreEqual(UnsafeUtility.AlignOf<T>(), (int)alignOf);
        
            if (index < 0 || index >= (int)length) throw new ArgumentOutOfRangeException();

            return UnsafeUtility.ReadArrayElement<T>(ptr, index);
        }

        public NativeArray<T>.ReadOnly AsReadOnly<T>() where T : unmanaged
        {
            Assert.AreEqual(UnsafeUtility.SizeOf<T>(), (int)sizeOf);
            Assert.AreEqual(UnsafeUtility.AlignOf<T>(), (int)alignOf);
        
            var nativeArray = NativeArrayUnsafeUtility.ConvertExistingDataToNativeArray<T>(ptr, (int)length, Allocator.None);
        
#if ENABLE_UNITY_COLLECTIONS_CHECKS
            NativeArrayUnsafeUtility.SetAtomicSafetyHandle(ref nativeArray, AtomicSafetyHandle.Create());
#endif
        
            return nativeArray.AsReadOnly();
        }
    }
}