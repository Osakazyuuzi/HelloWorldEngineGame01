#ifndef ___QUAT_H___
#define ___QUAT_H___

#include "Float3.h"

namespace Primitive
{
	/**
	@brief 4元数クラス
	*/
	class Quat
	{
	public:
		// 要素
		float x, y, z, w;

		/**
		@brief デフォルトコンストラクタ

		@note データを初期化しないままにします。
		*/
		Quat()
		{
		}

		/**
		@brief 引数付きコンストラクタ

		@note 実数部 w をスカラー値に設定し、虚数部 (x,y,z) をゼロに設定します。
		*/
		Quat(float r)
			: x(0.0f), y(0.0f), z(0.0f), w(r)
		{
		}

		/**
		@brief 引数付きコンストラクタ

		@note 4つのスカラーパラメーターで初期化します。

		@param nx 要素 X を初期化するための値。
		@param ny 要素 Y を初期化するための値。
		@param nz 要素 Z を初期化するための値。
		@param nw 要素 W を初期化するための値。
		*/
		Quat(float nx, float ny, float nz, float nw)
			: x(nx), y(ny), z(nz), w(nw)
		{
		}

		/**
		@brief 角度軸表現から作成します。

		@note 軸を正規化する必要があります!
		@note 角度はラジアン単位です!

		@note 単位:ラジアン
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
		@brief コピーコンストラクタ

		@param v コピー元
		*/
		Quat(const Quat& v)
			: x(v.x), y(v.y), z(v.z), w(v.w)
		{
		}

		/**
		@brief quat が単位数の場合に true を返します。
		*/
		bool isIdentity() const
		{
			return x == 0.0f && y == 0.0f && z == 0.0f && w == 1.0f;
		}

		/**
		@brief 2つの四元数が等しい場合に true を返します。
		*/
		bool operator==(const Quat& q) const
		{
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}

		/**
		@brief 四元数を角度軸表現に変換します。
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
		@brief 単位四元数の間の角度を取得します。

		@note 単位:ラジアン
		*/
		float getAngle() const
		{
			return acos(w) * 2.0f;
		}

		/**
		@brief 引数の四元数の間の角度を取得します。

		@note 単位:ラジアン
		*/
		float getAngle(const Quat& q) const
		{
			return acos(dot(q)) * 2.0f;
		}

		/**
		@brief 四元数の大きさの2乗であり、単位四元数の場合は1である必要があります。
		*/
		float magnitudeSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		/**
		@brief 引数の四元数との内積を返します。
		*/
		float dot(const Quat& v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		/**
		@brief 四元数を正規化した値を返します。
		*/
		Quat getNormalized() const
		{
			const float s = 1.0f / magnitude();
			return Quat(x * s, y * s, z * s, w * s);
		}

		/**
		@brief 四元数の大きさを返します。
		*/
		float magnitude() const
		{
			return sqrt(magnitudeSquared());
		}

		/**
		@brief 四元数を正規化し、正規化に使用した値を返します。
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
		@brief 虚部の符号が逆の四元数を返します。
		*/
		Quat getConjugate() const
		{
			return Quat(-x, -y, -z, w);
		}

		/**
		@brief 虚数部を返します。
		*/
		Float3 getImaginaryPart() const
		{
			return Float3(x, y, z);
		}

		/**
		@brief x軸の回転を計算します。
		*/
		Float3 getBasisVector0() const
		{
			const float x2 = x * 2.0f;
			const float w2 = w * 2.0f;
			return Float3((w * w2) - 1.0f * x * x2, (z * w2) + y * x2, (-y * w2) + z * x2);
		}

		/**
		@brief y軸の回転を計算します。
		*/
		Float3 getBasisVector1() const
		{
			const float y2 = y * 2.0f;
			const float w2 = w * 2.0f;
			return Float3((-z * w2) + x * y2, (w * w2) - 1.0f + y * y2, (x * w2) + z * y2);
		}

		/**
		@brief z軸の回転を計算します。
		*/
		Float3 getBasisVector2() const
		{
			const float z2 = z * 2.0f;
			const float w2 = w * 2.0f;
			return Float3((y * w2) + x * z2, (-x * w2) + y * z2, (w * w2) - 1.0f + z2);
		}

		/**
		@brief v を回転させます。（ユニタリと仮定）
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
		@brief v を逆回転させます。（ユニタリと仮定）
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
		@brief 代入演算子
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
		@brief 掛け算。
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
		@brief 足し算。
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
		@brief 引き算。
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
		@brief s でのスカラー倍の掛け算。
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
		@brief 四元数の掛け算。
		*/
		Quat operator*(const Quat& q) const
		{
			return Quat(w * q.x + q.w * x + y * q.z - q.y * z, w * q.y + q.w * y + z * q.x - q.z * x,
				w * q.z + q.w * z + x * q.y - q.x * y, w * q.w - x * q.x - y * q.y - z * q.z);
		}

		/**
		@brief 四元数の足し算。
		*/
		Quat operator+(const Quat& q) const
		{
			return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
		}

		/**
		@brief 逆の符号の四元数を返します。
		*/
		Quat operator-() const
		{
			return Quat(-x, -y, -z, -w);
		}

		/**
		@brief 四元数の引き算。
		*/
		Quat operator-(const Quat& q) const
		{
			return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
		}

		/**
		@brief r でのスカラー倍の掛け算。
		*/
		Quat operator*(float r) const
		{
			return Quat(x * r, y * r, z * r, w * r);
		}
	};
}
#endif //!___QUAT_H___