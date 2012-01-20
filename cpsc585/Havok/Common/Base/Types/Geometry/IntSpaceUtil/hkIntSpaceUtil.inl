/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's 
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok. 
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2011 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement. 
 */


#include <Common/Base/Math/Vector/hkIntVector.h>


void hkIntSpaceUtil::convertWithOffsetLow( const hkVector4& vIn, hkUint16 vOut[3] ) const
{
	hkVector4 v;
	v.setAdd( m_bitOffsetLow, vIn );
	v.mul( m_bitScale );

	hkIntVector imi; imi.setConvertF32toS32( v );

	hkIntVector vi;
	vi.setConvertU32ToU16( imi, imi );

	vOut[0] = vi.getU16<0>();
	vOut[1] = vi.getU16<1>();
	vOut[2] = vi.getU16<2>();
}

void hkIntSpaceUtil::transformPositionIntoIntSpace( hkVector4Parameter vecWorldSpace, hkVector4& vecIntSpaceOut ) const
{
	hkVector4 v;
	v.setAdd( m_bitOffsetLow, vecWorldSpace );
	v.mul( m_bitScale );
	vecIntSpaceOut = v;
}

void hkIntSpaceUtil::transformDirectionIntoIntSpace( hkVector4Parameter vecWorldSpace, hkVector4& vecIntSpaceOut ) const 
{
	vecIntSpaceOut.setMul( m_bitScale, vecWorldSpace );
}

void hkIntSpaceUtil::convertAabb(const hkAabb& aabbF, hkAabb16& aabbOut)const
{
	hkVector4 minVal; minVal.setZero();
	hkVector4 maxVal; maxVal.m_quad = s_aabb16Max;

	hkVector4 mi;  mi.setAdd( m_bitOffsetLow,  aabbF.m_min );
	hkVector4 ma;  ma.setAdd( m_bitOffsetHigh, aabbF.m_max );

	mi.mul( m_bitScale );
	ma.mul( m_bitScale );

	mi.setMax( minVal, mi );
	ma.setMax( minVal, ma );
	mi.setMin( maxVal, mi );
	ma.setMin( maxVal, ma );

	hkIntVector imi; imi.setConvertF32toS32( mi );
	hkIntVector ima; ima.setConvertF32toS32( ma );

	hkUint16 key0 = aabbOut.m_key;
	hkUint16 key1 = aabbOut.m_key1;
	((hkIntVector&)aabbOut).setConvertU32ToU16( imi, ima );

	aabbOut.m_key = key0;
	aabbOut.m_key1 = key1;
}


void hkIntSpaceUtil::restoreAabb(const hkAabb16& aabbI, hkAabb& aabbOut)const
{
	HK_ASSERT2( 0xf03dfdfe, (hkUlong(&aabbI)&0xf) == 0, "Your input data is not aligned");
	hkIntVector iZero; iZero.setZero();
	hkIntVector intAabb; intAabb.load<4>( (const hkUint32*)&aabbI);

	hkIntVector iMi; iMi.setCombineHead16To32( iZero, intAabb );
	hkIntVector iMa; iMa.setCombineTail16To32( iZero, intAabb );

	hkVector4 mi; iMi.convertS32ToF32( mi );
	hkVector4 ma; iMa.convertS32ToF32( ma );

	mi.mul( m_bitScaleInv );
	ma.mul( m_bitScaleInv );
	mi.sub( m_bitOffsetLow );
	ma.sub( m_bitOffsetHigh );

	aabbOut.m_min = mi;
	aabbOut.m_max = ma;

}

void hkIntSpaceUtil::convertIntToFloatAabbIntSpace(const hkAabb16& aabbI, hkAabb& aabbOut)
{
	HK_ASSERT2( 0xf03dfdfe, (hkUlong(&aabbI)&0xf) == 0, "Your input data is not aligned");
	hkIntVector iZero; iZero.setZero();
	hkIntVector intAabb; intAabb.load<4>( (const hkUint32*)&aabbI);

	hkIntVector iMi; iMi.setCombineHead16To32( iZero, intAabb );
	hkIntVector iMa; iMa.setCombineTail16To32( iZero, intAabb );

	hkVector4 mi; iMi.convertS32ToF32( mi );
	hkVector4 ma; iMa.convertS32ToF32( ma );

	aabbOut.m_min = mi;
	aabbOut.m_max = ma;
}

HK_FORCE_INLINE void hkIntSpaceUtil::convertIntToWorldSpace( const hkAabb& intSpaceAabb, hkAabb& worldSpaceAabbOut )
{
	hkVector4 mi = intSpaceAabb.m_min;
	hkVector4 ma = intSpaceAabb.m_max;

	mi.mul( m_bitScaleInv );
	ma.mul( m_bitScaleInv );
	mi.sub( m_bitOffsetLow );
	ma.sub( m_bitOffsetHigh );

	worldSpaceAabbOut.m_min = mi;
	worldSpaceAabbOut.m_max = ma;
}

/* 
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20110913) 
 *  
 * Confidential Information of Havok.  (C) Copyright 1999-2011 
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok 
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership 
 * rights, and intellectual property rights in the Havok software remain in 
 * Havok and/or its suppliers. 
 *  
 * Use of this software for evaluation purposes is subject to and indicates 
 * acceptance of the End User licence Agreement for this product. A copy of 
 * the license is included with this software and is also available at www.havok.com/tryhavok. 
 *  
 */
