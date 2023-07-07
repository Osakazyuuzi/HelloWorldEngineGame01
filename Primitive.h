#ifndef ___PRIMITIVE_H___
#define ___PRIMITIVE_H___

namespace Pirmitive
{
	//--- �萔
	#define NORMALIZATION_EPSILON float(1e-20f)	
	#define EPSILON float(1e-6f) // ���e�덷

	class Float3;			// float3
	typedef Float3 Point;	// �_
	class Vector3;			// �O�����x�N�g��
	class Line;				// ����
	class Segment;			// ����
	class Sphere;			// ��
	class Capsule;			// �J�v�Z��
	class AABB;				// AABB
}

#endif //!___PRIMITIVE_H___