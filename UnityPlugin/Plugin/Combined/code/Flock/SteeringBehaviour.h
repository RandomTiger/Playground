#pragma once

#include <math.h>
#include "Ogre3D/Vector3.h"
#include "FlockEntity.h"

class FlockEntity;

class SteeringBehaviour
{
public:
	enum Behaviour
	{
		Behaviour_flee = 1 << 0,
		Behaviour_separation = 1 << 1,
		Behaviour_allignment = 1 << 2,
		Behaviour_cohesion = 1 << 3,
		Behaviour_wander = 1 << 4,
		Behaviour_seek = 1 << 5,

		Behaviour_all = Behaviour_flee | Behaviour_separation | Behaviour_allignment | Behaviour_cohesion | Behaviour_wander | Behaviour_seek
	};

	SteeringBehaviour();
	Vector3 GetWanderTarget();
private:
	Vector3 m_WanderTarget;

    float m_WanderJitter;
    float m_WanderRadius;
	float m_WanderDistance;

    Vector3 m_SteeringForce;
    Behaviour m_Behaviour;
public:
	void SetBehaviours(Behaviour value);
	Vector3 Calc(const FlockEntity& entity, List<FlockEntity>& nearbyEntities, Vector3 target);
	bool On(Behaviour flag);

private:

    //---------------------- CalculatePrioritized ----------------------------
    //
    //  this method calls each active steering behavior in order of priority
    //  and acumulates their forces until the max steering force magnitude
    //  is reached, at which time the function returns the steering force 
    //  accumulated to that  point
    //------------------------------------------------------------------------
	Vector3 CalculatePrioritized(const FlockEntity& entity, List<FlockEntity>& nearby, Vector3 target);

    //--------------------- AccumulateForce ----------------------------------
    //
    //  This function calculates how much of its max steering force the 
    //  vehicle has left to apply and then applies that amount of the
    //  force to add.
    //------------------------------------------------------------------------
	bool AccumulateForce(const FlockEntity& entity, Vector3& RunningTot, Vector3 ForceToAdd);

    //---------------------- CalculateWeightedSum ----------------------------
    //
    //  this simply sums up all the active behaviors X their weights and 
    //  truncates the result to the max available steering force before 
    //  returning
    //------------------------------------------------------------------------
	Vector3 CalculateWeightedSum(const FlockEntity& entity, List<FlockEntity>& nearby, Vector3 target);

	Vector3 Flee(FlockEntity entity, Vector3 TargetPos);

    //---------------------------- Separation --------------------------------
    //
    // this calculates a force repelling from the other neighbors
    //------------------------------------------------------------------------
	Vector3 Separation(const FlockEntity& entity, List<FlockEntity>& nearby);

    //---------------------------- Alignment ---------------------------------
    //
    //  returns a force that attempts to align this agents heading with that
    //  of its neighbors
    //------------------------------------------------------------------------
	Vector3 Alignment(const FlockEntity& entity, List<FlockEntity> nearby);

    //-------------------------------- Cohesion ------------------------------
    //
    //  returns a steering force that attempts to move the agent towards the
    //  center of mass of the agents in its immediate area
    //------------------------------------------------------------------------
	Vector3 Cohesion(const FlockEntity& entity, List<FlockEntity>& nearby);

	Vector3 Seek(const FlockEntity& entity, Vector3 TargetPos);
   
	Vector3 Wander(const FlockEntity& entity);
};
