using UnityEngine;
using System.Collections;

public class MapChip : MonoBehaviour {
    public Quaternion invRot;
	// Use this for initialization
    void Awake()
    {
        if (invRot == null)
        {
            invRot = Quaternion.identity;
        }
    }
	void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
