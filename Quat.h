#ifndef ___QUAT_H___
#define ___QUAT_H___

#include "Float3.h"

namespace Primitive
{
	/**
	@brief 4�����N���X
	*/
	class Quat
	{
	public:
		// �v�f
		float x, y, z, w;

		/**
		@brief �f�t�H���g�R���X�g���N�^

		@note �f�[�^�����������Ȃ��܂܂ɂ��܂��B
		*/
		Quat()
		{
		}

		/**
		@brief �����t���R���X�g���N�^

		@note ������ w ���X�J���[�l�ɐݒ肵�A������ (x,y,z) ���[���ɐݒ肵�܂��B
		*/
		Quat(float r)
			: x(0.0f), y(0.0f), z(0.0f), w(r)
		{
		}

		/**
		@brief �����t���R���X�g���N�^

		@note 4�̃X�J���[�p�����[�^�[�ŏ��������܂��B

		@param nx �v�f X �����������邽�߂̒l�B
		@param ny �v�f Y �����������邽�߂̒l�B
		@param nz �v�f Z �����������邽�߂̒l�B
		@param nw �v�f W �����������邽�߂̒l�B
		*/
		Quat(float nx, float ny, float nz, float nw)
			: x(nx), y(ny), z(nz), w(nw)
		{
		}

		/**
		@brief �p�x���\������쐬���܂��B

		@note ���𐳋K������K�v������܂�!
		@note �p�x�̓��W�A���P�ʂł�!

		@note �P��:���W�A��
		*/
		Quat(float angleRadians, const Float3& unitAxis)
		{
			const float a = angleRadians * 0.5f;
			const float s = sin(a);
			w = cos(a);
			x = unitAxis.x * s;
			y = unitAxis.y * s;
			z = unitAxis.z * s;
		}

		/**
		@brief �R�s�[�R���X�g���N�^

		@param v �R�s�[��
		*/
		Quat(const Quat& v)
			: x(v.x), y(v.y), z(v.z), w(v.w)
		{
		}

		/**
		@brief quat ���P�ʐ��̏ꍇ�� true ��Ԃ��܂��B
		*/
		bool isIdentity() const
		{
			return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
		}

		/**
		@brief 2�̎l�������������ꍇ�� true ��Ԃ��܂��B
		*/
		bool operator==(const Quat& q) const
		{
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}

		/**
		@brief �l�������p�x���\���ɕϊ����܂��B
		*/
		void toRadiansAndUnitAxis(float& angle, Float3& axis) const
		{
			const float quatEpsilon = 1.0e-8f;
			const float s2 = x * x + y * y + z * z;
			if (s2 < quatEpsilon * quatEpsilon)
			{
				angle = 0.0f;
				axis = Float3(1.0f, 0.0f, 0.0f);
			}
			else
			{
				const float s = 1 / sqrt(s2);
				axis = Float3(x, y, z) * 2;
				angle = abs(w) < quatEpsilon ? 3.1415926535f : atan2(s2 * s, w) * 2.0f;
			}
		}

		/**
		@brief �P�ʎl�����̊Ԃ̊p�x���擾���܂��B

		@note �P��:���W�A��
		*/
		float getAngle() const
		{
			return acos(w) * 2.0f;
		}

		/**
		@brief �����̎l�����̊Ԃ̊p�x���擾���܂��B

		@note �P��:���W�A��
		*/
		float getAngle(const Quat& q) const
		{
			return acos(dot(q)) * 2.0f;
		}

		/**
		@brief �l�����̑傫����2��ł���A�P�ʎl�����̏ꍇ��1�ł���K�v������܂��B
		*/
		float magnitudeSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		/**
		@brief �����̎l�����Ƃ̓��ς�Ԃ��܂��B
		*/
		float dot(const Quat& v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		/**
		@brief �l�����𐳋K�������l��Ԃ��܂��B
		*/
		Quat getNormalized() const
		{
			const float s = 1.0f / magnitude();
			return Quat(x * s, y * s, z * s, w * s);
		}

		/**
		@brief �l�����̑傫����Ԃ��܂��B
		*/
		float magnitude() const
		{
			return sqrt(magnitudeSquared());
		}

		/**
		@brief �l�����𐳋K�����A���K���Ɏg�p�����l��Ԃ��܂��B
		*/
		float normalize()
		{
			const float mag = magnitude();
			if (mag != 0.0f)
			{
				const float imag = 1.0f / mag;

				x *= imag;
				y *= imag;
				z *= imag;
				w *= imag;
			}
			return mag;
		}

		/**
		@brief �����̕������t�̎l������Ԃ��܂��B
		*/
		Quat getConjugate() const
		{
			return Quat(-x, -y, -z, w);
		}

		/**
		@brief ��������Ԃ��܂��B
		*/
		Float3 getImaginaryPart() const
		{
			return Float3(x, y, z);
		}

		/**
		@brief x���̉�]���v�Z���܂��B
		*/
		Float3 getBasisVector0() const
		{
			const float x2 = x * 2.0f;
			const float w2 = w * 2.0f;
			return Float3((w * w2) - 1.0f * x * x2, (z * w2) + y * x2, (-y * w2) + z * x2);
		}

		/**
		@brief y���̉�]���v�Z���܂��B
		*/
		Float3 getBasisVector1() const
		{
			const float y2 = y * 2.0f;
			const float w2 = w * 2.0f;
			return Float3((-z * w2) + x * y2, (w * w2) - 1.0f + y * y2, (x * w2) + z * y2);
		}

		/**
		@brief z���̉�]���v�Z���܂��B
		*/
		Float3 getBasisVector2() const
		{
			const float z2 = z * 2.0f;
			const float w2 = w * 2.0f;
			return Float3((y * w2) + x * z2, (-x * w2) + y * z2, (w * w2) - 1.0f + z2);
		}

		/**
		@brief v ����]�����܂��B�i���j�^���Ɖ���j
		*/
		const Float3 rotate(const Float3& v) const
		{
			const float vx = 2.0f * v.x;
			const float vy = 2.0f * v.y;
			const float vz = 2.0f * v.z;
			const float w2 = w * w - 0.5f;
			const float dot2 = (x * vx + y * vy + z * vz);
			return Float3((vx * w2 + (y * vz - z * vy) * w + x * dot2)
				, (vy * w2 + (z * vx - x * vz) * w + y * dot2)
				, (vz * w2 + (x * vy - y * vx) * w + z * dot2));
		}

		/**
		@brief v ���t��]�����܂��B�i���j�^���Ɖ���j
		*/
		const Float3 rotateInv(const Float3& v) const
		{
			const float vx = 2.0f * v.x;
			const float vy = 2.0f * v.y;
			const float vz = 2.0f * v.z;
			const float w2 = w * w - 0.5f;
			const float dot2 = (x * vx + y * vy + z * vz);
			return Float3((vx * w2 + (y * vz - z * vy) * w + x * dot2)
				, (vy * w2 + (z * vx - x * vz) * w + y * dot2)
				, (vz * w2 + (x * vy - y * vx) * w + z * dot2));
		}

		/**
		@brief ������Z�q
		*/
		Quat& operator=(const Quat& p)
		{
			x = p.x;
			y = p.y;
			z = p.z;
			w = p.w;
			return *this;
		}

		/**
		@brief �|���Z�B
		*/
		Quat& operator*=(const Quat& q)
		{
			const float tx = w * q.x + q.w * x + y * q.z - q.y * z;
			const float ty = w * q.y + q.w * y + z * q.x - q.z * x;
			const float tz = w * q.z + q.w * z + x * q.y - q.x * y;

			w = w * q.w - q.x * x - y * q.y - q.z * z;
			x = tx;
			y = ty;
			z = tz;

			return *this;
		}


		/**
		@brief �����Z�B
		*/
		Quat& operator+=(const Quat& q)
		{
			x += q.x;
			y += q.y;
			z += q.z;
			w += q.w;
			return *this;
		}

		/**
		@brief �����Z�B
		*/
		Quat& operator-=(const Quat& q)
		{
			x -= q.x;
			y -= q.y;
			z -= q.z;
			w -= q.w;
			return *this;
		}

		/**
		@brief s �ł̃X�J���[�{�̊|���Z�B
		*/
		Quat& operator*=(const float s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
			return *this;
		}

		/**
		@brief �l�����̊|���Z�B
		*/
		Quat operator*(const Quat& q) const
		{
			return Quat(w * q.x + q.w * x + y * q.z - q.y * z, w * q.y + q.w * y + z * q.x - q.z * x,
				w * q.z + q.w * z + x * q.y - q.x * y, w * q.w - x * q.x - y * q.y - z * q.z);
		}

		/**
		@brief �l�����̑����Z�B
		*/
		Quat operator+(const Quat& q) const
		{
			return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
		}

		/**
		@brief �t�̕����̎l������Ԃ��܂��B
		*/
		Quat operator-() const
		{
			return Quat(-x, -y, -z, -w);
		}

		/**
		@brief �l�����̈����Z�B
		*/
		Quat operator-(const Quat& q) const
		{
			return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
		}

		/**
		@brief r �ł̃X�J���[�{�̊|���Z�B
		*/
		Quat operator*(float r) const
		{
			return Quat(x * r, y * r, z * r, w * r);
		}
	};
}
#endif //!___QUAT_H___