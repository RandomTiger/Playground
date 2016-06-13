using UnityEngine;
using System.Runtime.InteropServices;
using System;

public class Plugin : MonoBehaviour
{

#if UNITY_ANDROID && !UNITY_EDITOR
    [DllImport("libnative")]
#else
    [DllImport("native")]
#endif
    private static extern float add(float x, float y);

#if UNITY_ANDROID && !UNITY_EDITOR
    [DllImport("libnative")]
#else
    [DllImport("native")]
#endif
    private static extern float mult(float x, float y);

#if UNITY_ANDROID && !UNITY_EDITOR
    [DllImport("libnative")]
#else
    [DllImport("native")]
#endif
    private static extern float sub(float x, float y);

#if UNITY_ANDROID && !UNITY_EDITOR
    [DllImport("libnative")]
#else
    [DllImport("native")]
#endif
    public static extern bool TestFloatArray([In, Out] float[] floatArray, int size);

#if UNITY_ANDROID && !UNITY_EDITOR
    [DllImport("libnative")]
#else
    [DllImport("native")]
#endif
    public static extern void ProcessFlock([Out] float[] floatArray, int size, float delta);

#if UNITY_ANDROID && !UNITY_EDITOR
    [DllImport("libnative")]
#else
    [DllImport("native")]
#endif
    public static extern void FlockSetup([In, Out] float[] floatArray, int size);

    void Start()
	{
		Debug.Log("Test");

        // Calls the FooPluginFunction inside the plugin
        // And prints 5 to the console
        Debug.Log(add(1,1));
		Debug.Log(mult(2,4));
		Debug.Log(sub(3,2));

        float[] data = new float[100 * 6];

        System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
        stopwatch.Start();
        for(int i = 0; i < 100; i++)
        {
            TestFloatArray(data, data.Length);
        }
        stopwatch.Stop();

        Debug.Log("Time ms: " + ((float) stopwatch.ElapsedMilliseconds) / 100.0f);
        Debug.Log("Time ticks: " + ((float) stopwatch.ElapsedTicks) / 100.0f);

        for (int i = 0; i < data.Length; i++)
        {
            Debug.Log(data[i].ToString());
        }
    }

    public static void FlockSetup(float[] array)
    {
        FlockSetup(array, array.Length);
    }

    public static void FlockProcess(float [] array)
    {
        ProcessFlock(array, array.Length, Time.deltaTime);
    }
}