#pragma once

#ifndef VOGL_STATIC

#ifdef EXPORT
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif // EXPORT

#define EXTERN extern "C"

#else

#define API
#define EXTERN

#endif // !VOGL_STATIC

#ifndef VECTOR
#define VECTOR

namespace vogl 
{
	template<typename T>
	struct API Vector2
	{
		T x;
		T y;
		Vector2() {};
		Vector2(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		Vector2(T vec)
		{
			this->x = vec;
			this->y = vec;
		}
		void operator=(Vector2<T> vec)
		{
			this->x = vec.x;
			this->y = vec.y;
		}
		void operator=(T vec)
		{
			this->x = vec;
			this->y = vec;
		}
		bool operator==(Vector2<T> vec)
		{
			return this->x == vec.x and this->y == vec.y;
		}
		Vector2<T> operator+(Vector2<T>& vec)
		{
			return Vector2<T>(this->x + vec.x, this->y + vec.y);
		}
		Vector2<T> operator-(Vector2<T>& vec)
		{
			return Vector2<T>(this->x - vec.x, this->y - vec.y);
		}
		Vector2<T> operator+(T a)
		{
			return Vector2<T>(this->x + a, this->y + a);
		}
		Vector2<T> operator-(T a)
		{
			return Vector2<T>(this->x - a, this->y - a);
		}
		Vector2<T> operator*(Vector2<T>& vec)
		{
			return Vector2<T>(this->x * vec.x, this->y * vec.y);
		}
		Vector2<T> operator/(Vector2<T>& vec)
		{
			return Vector2<T>(this->x / vec.x, this->y / vec.y);
		}
		Vector2<T> operator*(T a)
		{
			return Vector2<T>(this->x * a, this->y * a);
		}
		Vector2<T> operator/(T a)
		{
			return Vector2<T>(this->x / a, this->y / a);
		}
		void operator+=(Vector2<T> vec)
		{
			this->x += vec.x;
			this->y += vec.y;
		}
		void operator-=(Vector2<T> vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
		}
		void operator*=(Vector2<T> vec)
		{
			this->x *= vec.x;
			this->y *= vec.y;
		}
		void operator/=(Vector2<T> vec)
		{
			this->x /= vec.x;
			this->y /= vec.y;
		}
		void operator+=(T a)
		{
			this->x += a;
			this->y += a;
		}
		void operator-=(T a)
		{
			this->x -= a;
			this->y -= a;
		}
		void operator*=(T a)
		{
			this->x *= a;
			this->y *= a;
		}
		void operator/=(T a)
		{
			this->x /= a;
			this->y /= a;
		}
	};

	template<typename T>
	struct API Vector3
	{
		T x;
		T y;
		T z;
		Vector3() {};
		Vector3(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		Vector3(T vec)
		{
			this->x = vec;
			this->y = vec;
			this->z = vec;
		}
		void operator=(Vector3<T> vec)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
		}
		void operator=(T vec)
		{
			this->x = vec;
			this->y = vec;
			this->z = vec;
		}
		bool operator==(Vector3<T> vec)
		{
			return this->x == vec.x and this->y == vec.y and this->z == vec.z;
		}
		Vector3<T> operator+(Vector3<T>& vec)
		{
			return Vector3<T>(this->x + vec.x, this->y + vec.y, this->z + vec.z);
		}
		Vector3<T> operator-(Vector3<T>& vec)
		{
			return Vector3<T>(this->x - vec.x, this->y - vec.y, this->z - vec.z);
		}
		Vector3<T> operator+(T a)
		{
			return Vector3<T>(this->x + a, this->y + a, this->z + a);
		}
		Vector3<T> operator-(T a)
		{
			return Vector3<T>(this->x - a, this->y - a, this->z - a);
		}
		Vector3<T> operator*(Vector3<T>& vec)
		{
			return Vector3<T>(this->x * vec.x, this->y * vec.y, this->z * vec.z);
		}
		Vector3<T> operator/(Vector3<T>& vec)
		{
			return Vector3<T>(this->x / vec.x, this->y / vec.y, this->z / vec.z);
		}
		Vector3<T> operator*(T a)
		{
			return Vector3<T>(this->x * a, this->y * a, this->z * a);
		}
		Vector3<T> operator/(T a)
		{
			return Vector3<T>(this->x / a, this->y / a, this->z / a);
		}
		void operator+=(Vector3<T> vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			this->z += vec.z;
		}
		void operator-=(Vector3<T> vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			this->z -= vec.z;
		}
		void operator*=(Vector3<T> vec)
		{
			this->x *= vec.x;
			this->y *= vec.y;
			this->z *= vec.z;
		}
		void operator/=(Vector3<T> vec)
		{
			this->x /= vec.x;
			this->y /= vec.y;
			this->z /= vec.z;
		}
		void operator+=(T a)
		{
			this->x += a;
			this->y += a;
			this->z += a;
		}
		void operator-=(T a)
		{
			this->x -= a;
			this->y -= a;
			this->z -= a;
		}
		void operator*=(T a)
		{
			this->x *= a;
			this->y *= a;
			this->z *= a;
		}
		void operator/=(T a)
		{
			this->x /= a;
			this->y /= a;
			this->z /= a;
		}
	};

	template<typename T>
	struct API Vector4
	{
		T x;
		T y;
		T z;
		T w;
		Vector4() {};
		Vector4(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		Vector4(T vec)
		{
			this->x = vec;
			this->y = vec;
			this->z = vec;
			this->w = vec;
		}
		Vector4(Vector2<T> vec1, Vector2<T> vec2)
		{
			this->x = vec1.x;
			this->y = vec1.y;
			this->z = vec2.x;
			this->w = vec2.y;
		}
		void operator=(Vector4<T> vec)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
			this->w = vec.w;
		}
		void operator=(T vec)
		{
			this->x = vec;
			this->y = vec;
			this->z = vec;
			this->w = vec;
		}
		bool operator==(Vector4<T> vec)
		{
			return this->x == vec.x and this->y == vec.y and this->z == vec.z and this->w == vec.w;
		}
		Vector4<T> operator+(Vector4<T>& vec)
		{
			return Vector4<T>(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
		}
		Vector4<T> operator-(Vector4<T>& vec)
		{
			return Vector4<T>(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
		}
		Vector4<T> operator+(T a)
		{
			return Vector4<T>(this->x + a, this->y + a, this->z + a, this->w + a);
		}
		Vector4<T> operator-(T a)
		{
			return Vector4<T>(this->x - a, this->y - a, this->z - a, this->w - a);
		}
		Vector4<T> operator*(Vector4<T>& vec)
		{
			return Vector4<T>(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w);
		}
		Vector4<T> operator/(Vector4<T>& vec)
		{
			return Vector4<T>(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w);
		}
		Vector4<T> operator*(T a)
		{
			return Vector4<T>(this->x * a, this->y * a, this->z * a, this->w * a);
		}
		Vector4<T> operator/(T a)
		{
			return Vector4<T>(this->x / a, this->y / a, this->z / a, this->w / a);
		}
		void operator+=(Vector4<T> vec)
		{
			this->x += vec.x;
			this->y += vec.y;
			this->z += vec.z;
			this->w += vec.w;
		}
		void operator-=(Vector4<T> vec)
		{
			this->x -= vec.x;
			this->y -= vec.y;
			this->z -= vec.z;
			this->w -= vec.w;
		}
		void operator*=(Vector4<T> vec)
		{
			this->x *= vec.x;
			this->y *= vec.y;
			this->z *= vec.z;
			this->w *= vec.w;
		}
		void operator/=(Vector4<T> vec)
		{
			this->x /= vec.x;
			this->y /= vec.y;
			this->z /= vec.z;
			this->w /= vec.w;
		}
		void operator+=(T a)
		{
			this->x += a;
			this->y += a;
			this->z += a;
			this->w += a;
		}
		void operator-=(T a)
		{
			this->x -= a;
			this->y -= a;
			this->z -= a;
			this->w -= a;
		}
		void operator*=(T a)
		{
			this->x *= a;
			this->y *= a;
			this->z *= a;
			this->w *= a;
		}
		void operator/=(T a)
		{
			this->x /= a;
			this->y /= a;
			this->z /= a;
			this->w /= a;
		}
	};
}
#endif // !VECTOR