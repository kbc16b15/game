using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;
using System.Text;

public class tkTools : EditorWindow
{
    GameObject selectLocObject = null;
    GameObject locationObject = null;
    string outputLocFilePath = null;
    [MenuItem("Window/tkTools")]
    static void Open()
    {
        GetWindow<tkTools>();
    }
    /// <summary>
    /// 配置ファイル出力関係のGUI
    /// </summary>
    void OnGUI_OutputLocFileGroup()
    {
        EditorGUILayout.LabelField("配置データの出力パス");
        outputLocFilePath = EditorGUILayout.TextField(outputLocFilePath);
        if (GUILayout.Button("出力") && outputLocFilePath != null && outputLocFilePath.Length > 0)
        {
            GameObject location = GameObject.Find("Location");
            Transform[] locs = location.GetComponentsInChildren<Transform>();
            string outputTxt = "";
            //マップチップを出力。
            foreach (Transform tr in locs)
            {
                MapChip mapChip = tr.GetComponent<MapChip>();
                if (!mapChip)
                {
                    //マップチップが取得できないオブジェクトは無視。
                    continue;
                }
                string modelName = TrimModelName(tr.name);
                outputTxt += string.Format("//{0}\n", modelName);
                outputTxt += "{\n";
                outputTxt += string.Format("\t\"{0}\",\n", modelName);
                outputTxt += string.Format("\tD3DXVECTOR3({0:f}f, {1:f}f, {2:f}f),             //平行移動\n", tr.position.x, tr.position.y, tr.position.z);
                Quaternion rot = tr.localRotation * mapChip.invRot;
                rot *= tr.parent.localRotation;
                outputTxt += string.Format("\tD3DXQUATERNION({0:f}f, {1:f}f, {2:f}f, {3:f}f ),  //回転\n", rot.x, rot.y, rot.z, rot.w);
                outputTxt += "},\n";
            }
            try
            {
                using (StreamWriter sw = new StreamWriter(outputLocFilePath, false, Encoding.UTF8))
                {
                    sw.Write(outputTxt);
                }
            }
            catch { }

            outputTxt = "";

        }

        EditorGUILayout.Separator();
        GUILayout.Box("", GUILayout.Width(this.position.width), GUILayout.Height(1));
        EditorGUILayout.Separator();
    }
    /// <summary>
    /// GUIの処理。
    /// </summary>
    void OnGUI()
    {
        EditorGUILayout.BeginVertical();
       
        EditorGUILayout.LabelField("配置するオブジェクトを選択");
        selectLocObject = EditorGUILayout.ObjectField(selectLocObject, typeof(GameObject), true) as GameObject;
        GUILayout.Button("テスト");
        if (GUILayout.Button("シーンに追加"))
        {
            //ボタンを押された。
            if (selectLocObject != null)
            {
                //配置する。
                //
                locationObject = GameObject.Find("Location");
                if(locationObject == null)
                {
                    locationObject = new GameObject("Location");
                }
                
                GameObject addObj = UnityEditor.PrefabUtility.InstantiatePrefab(selectLocObject) as GameObject;
                
                Vector3 scale = addObj.transform.localScale;
                scale.x *= -1.0f;
                addObj.transform.localScale = scale;
                addObj.transform.parent = locationObject.transform;
                MapChip chip = addObj.AddComponent<MapChip>();
                chip.invRot = Quaternion.Inverse(addObj.transform.localRotation);
            }
        }
        EditorGUILayout.Separator();
        GUILayout.Box("", GUILayout.Width(this.position.width), GUILayout.Height(1));
        EditorGUILayout.Separator();
        if (GUILayout.Button("選択しているオブジェクトをコピー"))
        {
            if (Selection.activeGameObject )
            {
                //選択中のオブジェクトがある。
                MapChip mapChip = Selection.activeGameObject.GetComponent<MapChip>();
                if (mapChip)
                {
                    GameObject addObj = Object.Instantiate(Selection.activeGameObject) as GameObject;
                    addObj.GetComponent<MapChip>().invRot = mapChip.invRot;
                    addObj.transform.parent = Selection.activeGameObject.transform.parent;
                    addObj.transform.localPosition = Selection.activeGameObject.transform.localPosition;
                    addObj.transform.localRotation = Selection.activeGameObject.transform.localRotation;
                    addObj.transform.localScale = Selection.activeGameObject.transform.localScale;
                    addObj.name = Selection.activeGameObject.name;
                    Selection.activeGameObject = addObj;

                }
                else
                {
                    //MapChipが設定されているオブジェクトしかコピーできません。
                    EditorUtility.DisplayDialog("エラー", "MapChipが設定されているオブジェクトしかコピーはできません。", "OK");
                }
            }
        }
        EditorGUILayout.Separator();
        GUILayout.Box("", GUILayout.Width(this.position.width), GUILayout.Height(1));
        EditorGUILayout.Separator();

        OnGUI_OutputLocFileGroup();

        EditorGUILayout.EndVertical();
    }
    void OnEnable()
    {
        outputLocFilePath = EditorPrefs.GetString("outputLocFilePath");
    }
    void OnDestroy()
    {
        EditorPrefs.SetString("outputLocFilePath", outputLocFilePath);
    }
    /// <summary>
    /// 名前から不要な文字をトリム
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    static string TrimModelName(string name)
    {
        string modelName = name.Split('(')[0];
        char[] trim = { ' ', '.' };
        while (true)
        {
            string trimString = modelName.TrimEnd(trim);
            if (trimString == modelName)
            {
                //トリムできた。
                break;
            }
            modelName = trimString;
        }
        return modelName;
    }
 
}
