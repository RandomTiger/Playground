#include "Ogre3D/Vector3.h"
#include "Ogre3D/Quaternion.h"
#include "FlockEntity.h"

float Time::deltaTime = 0.333f;

void FlockEntity::Start ()
{
	m_Velocity = Vector3::zero;
	m_Mass = 1;
	m_MaxSpeed = 10.0f;
	m_MaxForce = 10.0f;
	m_MaxTurnRate = 5.0f;
	m_Sight = 10.0f;
	m_Behaviours = SteeringBehaviour::Behaviour_all;

	WeightSeparation = 1;
	WeightAlignment = 1;
	WeightCohesion = 1;
	WeightWander = 1;
	WeightSeek = 1;
	WeightFlee = 1;

	Tagged = true;

    m_Steering.SetBehaviours(m_Behaviours);
}
	
void FlockEntity::UpdateInternal(List<FlockEntity> nearby, Vector3 target)
{
    Vector3 steer = m_Steering.Calc(*this, nearby, target);

    Vector3 accel = steer / m_Mass;

    m_Velocity += accel * Time::deltaTime;

    Vector3::ClampMagnitude(m_Velocity, m_MaxSpeed);

    RotateHeadingToFacePosition(Position() + m_Velocity);

    transform.position += (m_Velocity.magnitude() * Heading() * Time::deltaTime);
}

bool FlockEntity::RotateHeadingToFacePosition(Vector3 target)
{
    Vector3 toTarget = Vector3::Normalize(target - Position());

    //first determine the angle between the heading vector and the target
    float angle = (float) acos(Vector3::Dot(Heading(), toTarget));

    //return true if the player is facing the target
    if (angle < 0.00001)
    {
        return true;
    }

    //clamp the amount to turn to the max turn rate
    if (angle > m_MaxTurnRate)
    {
        angle = m_MaxTurnRate;
    }

    Vector3 newHeading = Vector3::RotateTowards(Heading(), toTarget, angle * Mathf::Deg2Rad * Time::deltaTime);
    LookAt(transform.position + newHeading);
    return false;
}

void FlockEntity::LookAt(Vector3 target)
{
//    transform.LookAt(target);
//     transform.rotation = Quaternion.LookRotation(target - transform.position);
    transform.rotation = LookAt(transform.position, target);
}

Quaternion FlockEntity::LookAt(Vector3 sourcePoint, Vector3 destPoint)
{
    Vector3 forwardVector = Vector3::Normalize(destPoint - sourcePoint);

    float dot = Vector3::Dot(Vector3::forward, forwardVector);

    if (fabs(dot - (-1.0f)) < 0.000001f)
    {
        return Quaternion(Vector3::up.x, Vector3::up.y, Vector3::up.z, Mathf::PI);
    }
    if (fabs(dot - (1.0f)) < 0.000001f)
    {
        return Quaternion::identity;
    }

    float rotAngle = (float)acos(dot);
    Vector3 rotAxis = Vector3::Cross(Vector3::forward, forwardVector);
    rotAxis = Vector3::Normalize(rotAxis);
    return CreateFromAxisAngle(rotAxis, rotAngle);
}

Quaternion FlockEntity::CreateFromAxisAngle(Vector3 axis, float angle)
{
    float halfAngle = angle * 0.5f;
    float s = (float)sin(halfAngle);
    Quaternion q;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = (float)cos(halfAngle);
    return q;
}
