#ifndef ___AABB_H___
#define ___AABB_H___

#include "Primitive.h"
#include "Float3.h"
#include "Point.h"

namespace Primitive
{
	class AABB
	{
	public:
		//--- �v�f
		Point p;	// ���S�_
		Float3 hl;	// �e���̕ӂ̒����̔���

		// �R���X�g���N�^
		AABB(){}
		AABB(const Point& p, const Float3& hl) : p(p), hl(hl){}

		// �ӂ̒������擾
		float lenX() { return hl.x * 2.0f; }
		float lenY() { return hl.y * 2.0f; }
		float lenZ() { return hl.z * 2.0f; }
		float len(int i) {
			return *((&hl.x) + i) * 2.0f;
		}
	};
}

#endif //!___AABB_H___