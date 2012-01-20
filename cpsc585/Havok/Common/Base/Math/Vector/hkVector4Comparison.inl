/* 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's 
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok. 
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2011 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement. 
 */



HK_FORCE_INLINE /*static*/ hkVector4Comparison::Mask HK_CALL hkVector4Comparison::getMaskForComponent(int i)
{
	// note check compile time assert in .cpp file
	HK_ASSERT2(0x2337f8c7, (i>=0) && (i<4), "Component index out of range" );
	return hkVector4Comparison::Mask(1 << i);
}

HK_FORCE_INLINE int hkVector4Comparison::getIndexOfLastComponentSet() const
{
	return s_maskToLastIndex[getMask()];
}

HK_FORCE_INLINE int hkVector4Comparison::getIndexOfFirstComponentSet() const
{
	return s_maskToFirstIndex[getMask()];
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
