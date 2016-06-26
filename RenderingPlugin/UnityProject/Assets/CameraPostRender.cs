using UnityEngine;
using System;
using System.Collections;
using System.Runtime.InteropServices;

public class CameraPostRender : MonoBehaviour
{
    Camera Cam;

    void Start()
    {
        Cam = GetComponent<Camera>();
    }

    void OnPostRender()
    {
        Debug.Log("" + Cam.projectionMatrix);

        UseRenderingPlugin.CameraPostRender();
    }
}
