using UnityEngine;

namespace CppWrapper
{
    [CreateAssetMenu(fileName = "Wrapper", menuName = "Cpp Wrapper", order = 1)]
    public class CppWrapperData : ScriptableObject
    {
        //public string folderPath;
        public string dllName;
        public string dllPath;
    }
}