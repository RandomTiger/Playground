#pragma once

#include "Ogre3D/Vector3.h"
#include "Ogre3D/Quaternion.h"
#include "List.h"
#include "Mathf.h"
#include "SteeringBehaviour.h"

class FlockEntity;

class Time
{
public:
	static float deltaTime;
};

class SteeringBehaviour;

class FlockEntity
{
public:
	Vector3 m_Velocity;
	float m_Mass;
	float m_MaxSpeed;
	float m_MaxForce;
	float m_MaxTurnRate;;
	float m_Sight;
	SteeringBehaviour::Behaviour m_Behaviours;

	float WeightSeparation;
	float WeightAlignment;
	float WeightCohesion;
	float WeightWander;
	float WeightSeek;
	float WeightFlee;

	bool Tagged;

	Vector3 Position;
	Vector3 Heading;

	SteeringBehaviour m_Steering;

	void Start();
	void UpdateInternal(List<FlockEntity> nearby, Vector3 target);
private:
	bool RotateHeadingToFacePosition(Vector3 target);
	void LookAt(Vector3 target);
	static Quaternion LookAt(Vector3 sourcePoint, Vector3 destPoint);
	static Quaternion CreateFromAxisAngle(Vector3 axis, float angle);

	class Transform
	{
	public:
		Vector3 position;
		Quaternion rotation;
	};
public:
	Transform transform;
};
