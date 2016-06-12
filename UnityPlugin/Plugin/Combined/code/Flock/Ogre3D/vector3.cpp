#if WIN_DLL_TESTER
#include "..\..\..\WindowsDLLTester\stdafx.h"
#endif

#include "Vector3.h"

void assert(bool state) {}

const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
