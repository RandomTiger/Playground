using UnityEngine;
using System.Collections;
using Battlehub.SplineEditor;

namespace SplineEditor
{
    public class SplineFollow : MonoBehaviour
    {
        public float Duration = 15.0f;
        public SplineBase Spline;
        public float Offset;
        private float m_t;

        private float Wrap(float t)
        {
            return (Duration + t % Duration) % Duration;
        }

        private void Update()
        {
            Move();
        }

        private void Move()
        {
            float t = Wrap(m_t + Offset * Duration / 50.0f);
            float v = Spline.GetVelocity(t / Duration).magnitude / 5.0f;

            if (m_t >= Duration)
            {
                m_t = (m_t - Duration) + Time.deltaTime / v;

            }
            else
            {
                m_t += Time.deltaTime / v;
            }
           
            Vector3 position = Spline.GetPoint(t / Duration);
            Vector3 dir = Spline.GetDirection(t / Duration);
            float twist = Spline.GetTwist(t / Duration);

            transform.position = position;
            transform.LookAt(position + dir);
            transform.RotateAround(position, dir, twist);


        }

    }

}
