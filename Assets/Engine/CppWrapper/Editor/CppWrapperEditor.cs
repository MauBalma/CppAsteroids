using System.IO;
using CppWrapper;
using UnityEditor;
using UnityEngine;

[CustomEditor(typeof(CppWrapperData))]
public class CppWrapperDataEditor : Editor 
{
    private CppWrapperData comp;

    public override void OnInspectorGUI()
    {
        base.OnInspectorGUI();
        
        var data = (CppWrapperData)target;

        if (GUILayout.Button("Generate"))
        {
            var fileInfo = new FileInfo(AssetDatabase.GetAssetPath(data));
            var folder = fileInfo.Directory.FullName;

            var path = Path.Join(folder, data.dllName + ".g.cs");

            var generatedString = CppWrapper.CppWrapper.Generate(data.dllName, data.dllPath, folder);
            
            if (File.Exists(path))
            {
                var text = File.ReadAllText(path);
                if (text == generatedString) return;
            }
            
            if (File.Exists(path) && new FileInfo(path).Attributes.HasFlag(FileAttributes.ReadOnly))
            {
                Debug.LogError($"CODE GENERATOR: File {path} is mark as ReadOnly");
                return;
            } 
            
            File.WriteAllText(path, generatedString);
            
            AssetDatabase.Refresh();
            AssetDatabase.SaveAssets();
        }
    }

}