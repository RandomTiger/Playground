using UnityEngine;
using System.Collections.Generic;

[System.Serializable]
public struct Vector3i
{
    public Vector3i(int x, int y, int z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    public int x, y, z;
}

public class FlockManager : MonoBehaviour
{
    public GameObject EntityPrefab;
    public int Quantity = 30;
    public GameObject Target;
    bool SpatialPartition = false;
    public int SpatialDivide = 10;

    List<FlockEntity> m_Entities = new List<FlockEntity>();
    float[] m_EntityArray;
    int dataStride = 3 + 4; // pos + orientation

    BasicSP<FlockEntity> m_BasicSP;

    void Start()
    {
        int i, data;

        m_BasicSP = new BasicSP<FlockEntity>(new Vector3i(SpatialDivide, SpatialDivide, SpatialDivide), new Vector3(-50f, -50f, -50f), new Vector3(50f, 50f, 50f));

        for (i = 0; i < Quantity; i++)
        {
            FlockEntity entity = Instantiate(EntityPrefab).GetComponent<FlockEntity>();
            m_Entities.Add(entity);

            // Group them under manager so they dont swamp the scene hierarchy 
            entity.transform.parent = transform;
            entity.m_Velocity = Vector3.forward;
            entity.transform.position = Random.insideUnitSphere * 10;
        }

        m_EntityArray = new float[m_Entities.Count * dataStride];

        for (i = 0, data = 0; i < m_Entities.Count; i++, data += dataStride)
        {
            m_EntityArray[i * dataStride + 0] = m_Entities[i].transform.position.x;
            m_EntityArray[i * dataStride + 1] = m_Entities[i].transform.position.y;
            m_EntityArray[i * dataStride + 2] = m_Entities[i].transform.position.z;

            m_EntityArray[i * dataStride + 3] = m_Entities[i].transform.rotation.x;
            m_EntityArray[i * dataStride + 4] = m_Entities[i].transform.rotation.y;
            m_EntityArray[i * dataStride + 5] = m_Entities[i].transform.rotation.z;
            m_EntityArray[i * dataStride + 6] = m_Entities[i].transform.rotation.w;
        }

        Plugin.FlockSetup(m_EntityArray);
    }

    void Update()
    {
        long local = UpdateLocal();
        long plugin = UpdatePlugin();

        Debug.Log("C++ to C# " + (local / (float)plugin));
    }

    long UpdateLocal()
    { 
        List<FlockEntity> nearbyEntities = new List<FlockEntity>();
        if(SpatialPartition)
        {
            m_BasicSP.Update(m_Entities);
        }

        System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
        stopwatch.Start();

        if (SpatialPartition == false)
        {
            nearbyEntities = m_Entities;
        }

        for (int i = 0; i < m_Entities.Count; i++)
        {
            if(SpatialPartition)
            {
                m_BasicSP.GetEntitiesInRange(ref nearbyEntities, m_Entities[i].Position, m_Entities[i].m_Sight);
            }

            m_Entities[i].Tagged = false;
            // Dont use Unity update per entity, its not efficent on mobile
            m_Entities[i].UpdateInternal(nearbyEntities, Target.transform.position); 
            m_Entities[i].Tagged = true;
        }

        stopwatch.Stop();

        Debug.Log("Flock C#  " + stopwatch.ElapsedMilliseconds + "ms " + stopwatch.ElapsedTicks + " ticks");
        return stopwatch.ElapsedTicks;
    }

    long UpdatePlugin()
    {
        System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
        stopwatch.Start();

        Plugin.FlockProcess(m_EntityArray);

        int i, data;
        for (i = 0, data = 0; i < m_Entities.Count; i++, data += dataStride)
        {
            m_Entities[i].transform.position = new Vector3(m_EntityArray[dataStride + 0], m_EntityArray[dataStride + 1], m_EntityArray[dataStride + 2]);
            m_Entities[i].transform.rotation = new Quaternion(m_EntityArray[dataStride + 3], m_EntityArray[dataStride + 4], m_EntityArray[dataStride + 5], m_EntityArray[dataStride + 6]);
        }

        stopwatch.Stop();

        Debug.Log("Flock C++ " + stopwatch.ElapsedMilliseconds + "ms " + stopwatch.ElapsedTicks + " ticks");
        return stopwatch.ElapsedTicks;
    }

    void OnDrawGizmos()
    {
        if(m_BasicSP != null)
        {
            m_BasicSP.OnDrawGizmos();
        }
    }
}
