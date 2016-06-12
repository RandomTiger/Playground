#if WIN_DLL_TESTER
#include "..\..\..\WindowsDLLTester\stdafx.h"
#endif

/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2016 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "Quaternion.h"

const Real Quaternion::msEpsilon = (float) 1e-03;
const Quaternion Quaternion::ZERO(0,0,0,0);
const Quaternion Quaternion::IDENTITY(1,0,0,0);

const Quaternion Quaternion::identity = IDENTITY;

//-----------------------------------------------------------------------
Vector3 Quaternion::xAxis(void) const
{
    //Real fTx  = 2.0*x;
    Real fTy  = 2.0f*y;
    Real fTz  = 2.0f*z;
    Real fTwy = fTy*w;
    Real fTwz = fTz*w;
    Real fTxy = fTy*x;
    Real fTxz = fTz*x;
    Real fTyy = fTy*y;
    Real fTzz = fTz*z;

    return Vector3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
}
//-----------------------------------------------------------------------
Vector3 Quaternion::yAxis(void) const
{
    Real fTx  = 2.0f*x;
    Real fTy  = 2.0f*y;
    Real fTz  = 2.0f*z;
    Real fTwx = fTx*w;
    Real fTwz = fTz*w;
    Real fTxx = fTx*x;
    Real fTxy = fTy*x;
    Real fTyz = fTz*y;
    Real fTzz = fTz*z;

    return Vector3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
}
//-----------------------------------------------------------------------
Vector3 Quaternion::zAxis(void) const
{
    Real fTx  = 2.0f*x;
    Real fTy  = 2.0f*y;
    Real fTz  = 2.0f*z;
    Real fTwx = fTx*w;
    Real fTwy = fTy*w;
    Real fTxx = fTx*x;
    Real fTxz = fTz*x;
    Real fTyy = fTy*y;
    Real fTyz = fTz*y;

    return Vector3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
}

//-----------------------------------------------------------------------
Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
{
    return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator- (const Quaternion& rkQ) const
{
    return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator* (const Quaternion& rkQ) const
{
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.

    return Quaternion
    (
        w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
        w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
        w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
        w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
    );
}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator* (Real fScalar) const
{
    return Quaternion(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
}
//-----------------------------------------------------------------------
Quaternion operator* (Real fScalar, const Quaternion& rkQ)
{
    return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
        fScalar*rkQ.z);
}
//-----------------------------------------------------------------------
Quaternion Quaternion::operator- () const
{
    return Quaternion(-w,-x,-y,-z);
}
//-----------------------------------------------------------------------
Real Quaternion::Dot (const Quaternion& rkQ) const
{
    return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
}
//-----------------------------------------------------------------------
Real Quaternion::Norm () const
{
    return w*w+x*x+y*y+z*z;
}
//-----------------------------------------------------------------------
Quaternion Quaternion::Inverse () const
{
    Real fNorm = w*w+x*x+y*y+z*z;
    if ( fNorm > 0.0 )
    {
        Real fInvNorm = 1.0f/fNorm;
        return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
    }
    else
    {
        // return an invalid result to flag the error
        return ZERO;
    }
}
//-----------------------------------------------------------------------
Quaternion Quaternion::UnitInverse () const
{
    // assert:  'this' is unit length
    return Quaternion(w,-x,-y,-z);
}

//-----------------------------------------------------------------------
Vector3 Quaternion::operator* (const Vector3& v) const
{
	// nVidia SDK implementation
	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = qvec.crossProduct(v);
	uuv = qvec.crossProduct(uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;

}
//-----------------------------------------------------------------------
bool Quaternion::equals(const Quaternion& rhs, const Radian& tolerance) const
{
    Real d = Dot(rhs);
    Radian angle = (float)acos(2.0f * d*d - 1.0f);

	return fabs(angle) <= tolerance;
}
//-----------------------------------------------------------------------
Quaternion Quaternion::Slerp (Real fT, const Quaternion& rkP,
    const Quaternion& rkQ, bool shortestPath)
{
    Real fCos = rkP.Dot(rkQ);
    Quaternion rkT;

    // Do we need to invert rotation?
    if (fCos < 0.0f && shortestPath)
    {
        fCos = -fCos;
        rkT = -rkQ;
    }
    else
    {
        rkT = rkQ;
    }

    if (fabs(fCos) < 1 - msEpsilon)
    {
        // Standard case (slerp)
        Real fSin = (float)sqrt(1 - fCos*fCos);
        Radian fAngle = (float)atan2(fSin, fCos);
        Real fInvSin = 1.0f / fSin;
        Real fCoeff0 = (float)sin((1.0f - fT) * fAngle) * fInvSin;
        Real fCoeff1 = (float)sin(fT * fAngle) * fInvSin;
        return fCoeff0 * rkP + fCoeff1 * rkT;
    }
    else
    {
        // There are two situations:
        // 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
        //    interpolation safely.
        // 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
        //    are an infinite number of possibilities interpolation. but we haven't
        //    have method to fix this case, so just use linear interpolation here.
        Quaternion t = (1.0f - fT) * rkP + fT * rkT;
        // taking the complement requires renormalisation
        t.normalise();
        return t;
    }
}
//-----------------------------------------------------------------------
Quaternion Quaternion::SlerpExtraSpins (Real fT,
    const Quaternion& rkP, const Quaternion& rkQ, int iExtraSpins)
{
    Real fCos = rkP.Dot(rkQ);
    Radian fAngle ((float)acos(fCos) );

    if ( fabs(fAngle) < msEpsilon )
        return rkP;

    Real fSin = (float)sin(fAngle);
    Radian fPhase ((float)M_PI*iExtraSpins*fT );
    Real fInvSin = 1.0f/fSin;
    Real fCoeff0 = (float)sin((1.0f-fT)*fAngle - fPhase)*fInvSin;
    Real fCoeff1 = (float)sin(fT*fAngle + fPhase)*fInvSin;
    return fCoeff0*rkP + fCoeff1*rkQ;
}

//-----------------------------------------------------------------------
Quaternion Quaternion::Squad (Real fT,
    const Quaternion& rkP, const Quaternion& rkA,
    const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath)
{
    Real fSlerpT = 2.0f*fT*(1.0f-fT);
    Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
    Quaternion kSlerpQ = Slerp(fT, rkA, rkB);
    return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
}
//-----------------------------------------------------------------------
Real Quaternion::normalise(void)
{
    Real len = Norm();
    Real factor = 1.0f / (float) sqrt(len);
    *this = *this * factor;
    return len;
}
//-----------------------------------------------------------------------
Radian Quaternion::getRoll(bool reprojectAxis) const
{
	if (reprojectAxis)
	{
		// roll = atan2(localx.y, localx.x)
		// pick parts of xAxis() implementation that we need
//			Real fTx  = 2.0*x;
		Real fTy  = 2.0f*y;
		Real fTz  = 2.0f*z;
		Real fTwz = fTz*w;
		Real fTxy = fTy*x;
		Real fTyy = fTy*y;
		Real fTzz = fTz*z;

		// Vector3(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);

		return Radian(atan2(fTxy+fTwz, 1.0f-(fTyy+fTzz)));

	}
	else
	{
		return Radian(atan2(2*(x*y + w*z), w*w + x*x - y*y - z*z));
	}
}
//-----------------------------------------------------------------------
Radian Quaternion::getPitch(bool reprojectAxis) const
{
	if (reprojectAxis)
	{
		// pitch = atan2(localy.z, localy.y)
		// pick parts of yAxis() implementation that we need
		Real fTx  = 2.0f*x;
//			Real fTy  = 2.0f*y;
		Real fTz  = 2.0f*z;
		Real fTwx = fTx*w;
		Real fTxx = fTx*x;
		Real fTyz = fTz*y;
		Real fTzz = fTz*z;

		// Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
		return Radian(atan2(fTyz+fTwx, 1.0f-(fTxx+fTzz)));
	}
	else
	{
		// internal version
		return Radian(atan2(2*(y*z + w*x), w*w - x*x - y*y + z*z));
	}
}
//-----------------------------------------------------------------------
Radian Quaternion::getYaw(bool reprojectAxis) const
{
	if (reprojectAxis)
	{
		// yaw = atan2(localz.x, localz.z)
		// pick parts of zAxis() implementation that we need
		Real fTx  = 2.0f*x;
		Real fTy  = 2.0f*y;
		Real fTz  = 2.0f*z;
		Real fTwy = fTy*w;
		Real fTxx = fTx*x;
		Real fTxz = fTz*x;
		Real fTyy = fTy*y;

		// Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

		return Radian(atan2(fTxz+fTwy, 1.0f-(fTxx+fTyy)));

	}
	else
	{
		// internal version
		return Radian(asin(-2*(x*z - w*y)));
	}
}
//-----------------------------------------------------------------------
Quaternion Quaternion::nlerp(Real fT, const Quaternion& rkP,
    const Quaternion& rkQ, bool shortestPath)
{
	Quaternion result;
    Real fCos = rkP.Dot(rkQ);
	if (fCos < 0.0f && shortestPath)
	{
		result = rkP + fT * ((-rkQ) - rkP);
	}
	else
	{
		result = rkP + fT * (rkQ - rkP);
	}
    result.normalise();
    return result;
}
