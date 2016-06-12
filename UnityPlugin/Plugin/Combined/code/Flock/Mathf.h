#pragma once

class Vector3;

class Mathf
{
public:
	static float Deg2Rad;
	static float Rad2Deg;
	static float PI;
};

class Random
{
public:
	static Vector3 insideUnitSphere();
};