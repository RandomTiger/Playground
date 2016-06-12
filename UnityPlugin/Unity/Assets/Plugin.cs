using UnityEngine;
using System.Runtime.InteropServices;

public class Plugin : MonoBehaviour
{
#if UNITY_ANDROID && !UNITY_EDITOR
	[DllImport("libnative")]

	private static extern float add(float x, float y);

	[DllImport("libnative")]
	private static extern float mult(float x, float y);
#else
	[DllImport("native")]

	private static extern float add(float x, float y);

	[DllImport("native")]
	private static extern float mult(float x, float y);
#endif

	void Start()
	{
		Debug.Log("Test");

		// Calls the FooPluginFunction inside the plugin
		// And prints 5 to the console
		Debug.Log(add(1,1));
		Debug.Log(mult(2,4));
	}
}