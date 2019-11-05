#pragma once


#ifndef VEC2
#define VEC2

class Vec2
{
private:
	static int vec2Size;
public:
	float x;
	float y;

	Vec2() = default;
	Vec2(float a) : x(a), y(a) {};
	Vec2(float a, float b) : x(a), y(b) {};
	Vec2(const Vec2 &src) : x(src.x), y(src.y) {};
	~Vec2() {}

	float getU() { return x; }
	float getV() { return y; }
	void setU(float u) { x = u; }
	void setV(float v) { y = v; }

	static int size() { return vec2Size; }

	Vec2 operator-()const { Vec2 tempVec(-x, -y); return tempVec; }
	Vec2 operator=(const Vec2 &value) { x = value.x; y = value.y; return *this; }
	Vec2 operator=(const float value) { x = value; y = value; return *this; }
	Vec2 operator+(const Vec2 &value) { Vec2 tempVec; tempVec.x = x + value.x; tempVec.y = y + value.y; return tempVec; }	
	Vec2 operator-(const Vec2 &value) { Vec2 tempVec; tempVec.x = x - value.x; tempVec.y = y - value.y; return tempVec; }
	Vec2& operator+=(const Vec2 &value) { x = x + value.x; y = y + value.y; return *this; }
	Vec2& operator+=(const float value) { x = x + value; y = y + value; return *this; }
	Vec2& operator-=(const Vec2 &value) { x = x - value.x; y = y - value.y; return *this; }
	Vec2& operator-=(const float value) { x = x - value; y = y - value; return *this; }
	Vec2& operator*=(const float value) { x = x * value; y = y * value; return *this; }
	Vec2& operator/=(const float value) {
		if (value != 0) {
			x = x / value; y = y / value; return *this;
		}
		else {
			x = 0.0f; y = 0.0f; return *this;
		}
	}
	
	float squareLength() const{
		return (x * x + y * y);
	}
	
	float length() const {
		return sqrt(squareLength());
	}
	Vec2 normalize() const {
		float len = this->length();
		if (len != 0.0f) {
			Vec2 normVec2(x / len, y / len);
			return normVec2;
		}
		else {
			Vec2 normVec2(0.0f);
			return normVec2;
		}	
	}
};

int Vec2::vec2Size = 2;

inline Vec2 operator+(const Vec2 &vec, const float value) { return Vec2(vec.x + value, vec.y + value); }
inline Vec2 operator+(const float value, const Vec2 &vec) { return Vec2(vec.x + value, vec.y + value); }

inline Vec2 operator-(const Vec2 &vec, const float value) { return Vec2(vec.x - value, vec.y - value); }
inline Vec2 operator-(const float value, const Vec2 &vec) { return Vec2(value - vec.x, value - vec.y); }

inline Vec2 operator*(const Vec2 &vec, const float value) { return Vec2(vec.x * value, vec.y * value); }
inline Vec2 operator*(const float value, const Vec2 &vec) { return Vec2(value * vec.x, value * vec.y); }

inline Vec2 operator/(const Vec2 &vec, const float value) {
	if (value != 0) {
		return Vec2(vec.x / value, vec.y / value);
	}
	else {
		return Vec2(0.0f);
	}
}

inline float dot(const Vec2 &vec1, const Vec2 &vec2) { return (vec1.x * vec2.x + vec1.y * vec2.y); }
inline float cross(const Vec2 &vec1, const Vec2 &vec2) { return (vec1.x * vec2.y - vec1.y * vec2.x); }

#endif//endif VEC2


#ifndef VEC3
#define VEC3

class Vec3
{
private:
	static int vec3Size;
public:
	float x;
	float y;
	float z;

	Vec3() = default;
	Vec3(float a) : x(a), y(a),z(a) {};
	Vec3(float a, float b, float c) : x(a), y(b), z(c) {};
	Vec3(const Vec3 &src) : x(src.x), y(src.y), z(src.z) {};
	Vec3(const Vec4 &src) : x(src.x), y(src.y), z(src.z) {};
	~Vec3() {}

	float getR() { return x; }
	float getG() { return y; }
	float getB() { return z; }
	void setR(float r) { x = r; }
	void setG(float g) { y = g; }
	void setB(float b) { y = b; }

	static int size() { return vec3Size; }

	Vec3 operator-()const { Vec3 tempVec(-x, -y, -z); return tempVec; }
	Vec3 operator=(const Vec3 &value) { x = value.x; y = value.y; z = value.z; return *this; }
	Vec3 operator=(const float value) { x = value; y = value; z = value; return *this; }
	Vec3 operator+(const Vec3 &value) { Vec3 tempVec; tempVec.x = x + value.x; tempVec.y = y + value.y; tempVec.z = z + value.z;  return tempVec; }
	Vec3 operator-(const Vec3 &value) { Vec3 tempVec; tempVec.x = x - value.x; tempVec.y = y - value.y; tempVec.z = z - value.z; return tempVec; }
	Vec3& operator+=(const Vec3 &value) { x = x + value.x; y = y + value.y; z = z + value.z; return *this; }
	Vec3& operator+=(const float value) { x = x + value; y = y + value; z = z + value; return *this; }
	Vec3& operator-=(const Vec3 &value) { x = x - value.x; y = y - value.y; z = z - value.z; return *this; }
	Vec3& operator-=(const float value) { x = x - value; y = y - value; z = z - value; return *this; }
	Vec3& operator*=(const float value) { x = x * value; y = y * value; z = z * value; return *this; }
	Vec3& operator/=(const float value) { 
		if (value != 0) {
			x = x / value; y = y / value; z = z / value; return *this;
		}
		else {
			x = 0.0f; y = 0.0f; z = 0.0f; return *this;
		}
	}

	float squareLength() const {
		return (x * x + y * y + z * z);
	}

	float length() const {
		return sqrt(squareLength());
	}

	Vec3 normalize() const {
		float len = this->length();
		if (len != 0) {
			Vec3 normVec3(x / len, y / len, z / len);
			return normVec3;
		}
		else {
			Vec3 normVec3(0.0f);
			return normVec3;
		}
	}

	Vec4 toVec4() const {
		return Vec4(this);
	}
};

int Vec3::vec3Size = 3;

inline Vec3 operator+(const Vec3 &vec, const float value) { return Vec3(vec.x + value, vec.y + value, vec.z +value); }
inline Vec3 operator+(const float value, const Vec3 &vec) { return Vec3(vec.x + value, vec.y + value, vec.z + value); }

inline Vec3 operator-(const Vec3 &vec, const float value) { return Vec3(vec.x - value, vec.y - value, vec.z - value); }
inline Vec3 operator-(const float value, const Vec3 &vec) { return Vec3(value - vec.x, value - vec.y, value - vec.z); }

inline Vec3 operator*(const Vec3 &vec, const float value) { return Vec3(vec.x * value, vec.y * value, vec.z * value); }
inline Vec3 operator*(const float value, const Vec3 &vec) { return Vec3(value * vec.x, value * vec.y, value * vec.z); }

inline Vec3 operator/(const Vec3 &vec, const float value) { 
	if (value != 0) {
		return Vec3(vec.x / value, vec.y / value, vec.z / value);
	}
	else {
		return Vec3(0.0f);
	}
 }

inline float dot(const Vec3 &vec1, const Vec3 &vec2) { return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z); }
inline Vec3 cross(const Vec3 &vec1, const Vec3 &vec2) { 
	////////////////////////////////////////不确定
	return Vec3(
		(vec1.y * vec2.z - vec2.y * vec1.z),
		-(vec1.x * vec2.z - vec2.x * vec1.z),
		(vec1.x * vec2.y - vec2.x * vec1.y)); 
}

#endif//endif VEC3


#ifndef VEC4
#define VEC4

class Vec4
{
private:
	static int vec4Size;
public:
	float x;
	float y;
	float z;
	float w;

	Vec4() = default;
	Vec4(float a) : x(a), y(a), z(a), w(a) {};
	Vec4(float a, float b, float c, float d = 0.0f) : x(a), y(b), z(c), w(d){};
	Vec4(const Vec3 &src) : x(src.x), y(src.y), z(src.z), w(0.0f) {};
	Vec4(const Vec4 &src) : x(src.x), y(src.y), z(src.z), w(src.w) {};
	~Vec4() {}

	float getR() const { return x; }
	float getG() const { return y; }
	float getB() const { return z; }
	float getA() const { return w; }
	void setR(float r) { x = r; }
	void setG(float g) { y = g; }
	void setB(float b) { y = b; }
	void setA(float a) { y = a; }

	static int size() { return vec4Size; }

	Vec4 operator-()const { Vec4 tempVec(-x, -y, -z, -w); return tempVec; }
	Vec4 operator=(const Vec4 &value) { x = value.x; y = value.y; z = value.z; w = value.w; return *this; }
	Vec4 operator=(const float value) { x = value; y = value; z = value; w = value; return *this; }
	Vec4 operator+(const Vec4 &value) { Vec4 tempVec; tempVec.x = x + value.x; tempVec.y = y + value.y; tempVec.z = z + value.z; tempVec.w = w + value.w;  return tempVec; }
	Vec4 operator-(const Vec4 &value) { Vec4 tempVec; tempVec.x = x - value.x; tempVec.y = y - value.y; tempVec.z = z - value.z; tempVec.w = w - value.w; return tempVec; }
	Vec4& operator+=(const Vec4 &value) { x = x + value.x; y = y + value.y; z = z + value.z; w = w + value.w; return *this; }
	Vec4& operator+=(const float value) { x = x + value; y = y + value; z = z + value; w = w + value; return *this; }
	Vec4& operator-=(const Vec4 &value) { x = x - value.x; y = y - value.y; z = z - value.z; w = w - value.w; return *this; }
	Vec4& operator-=(const float value) { x = x - value; y = y - value; z = z - value; w = w + value; return *this; }
	Vec4& operator*=(const float value) { x = x * value; y = y * value; z = z * value; w = w * value; return *this; }
	Vec4& operator/=(const float value) {
		if (value != 0) {
			x = x / value; y = y / value; z = z / value; w = w / value; return *this;
		}
		else {
			x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; return *this;
		}
	}

	float squareLength() const {
		return (x * x + y * y + z * z + w * w);
	}

	float length() const {
		return sqrt(squareLength());
	}
	Vec4 normalize() const {
		float len = this->length();
		if (len != 0) {
			Vec4 normVec4(x / len, y / len, z / len, w / len);
			return normVec4;
		}
		else {
			Vec4 normVec4(0.0f);
			return normVec4;
		}
		
	}

	Vec3 toVec3() const {
		return Vec3(this);
	}
};

int Vec4::vec4Size = 4;

inline Vec4 operator+(const Vec4 &vec, const float value) { return Vec4(vec.x + value, vec.y + value, vec.z + value, vec.w + value); }
inline Vec4 operator+(const float value, const Vec4 &vec) { return Vec4(vec.x + value, vec.y + value, vec.z + value, vec.w + value); }

inline Vec4 operator-(const Vec4 &vec, const float value) { return Vec4(vec.x - value, vec.y - value, vec.z - value, vec.w - value); }
inline Vec4 operator-(const float value, const Vec4 &vec) { return Vec4(value - vec.x, value - vec.y, value - vec.z, value - vec.w); }

inline Vec4 operator*(const Vec4 &vec, const float value) { return Vec4(vec.x * value, vec.y * value, vec.z * value, vec.z * value); }
inline Vec4 operator*(const float value, const Vec4 &vec) { return Vec4(value * vec.x, value * vec.y, value * vec.z, value * vec.w); }

inline Vec4 operator/(const Vec4 &vec, const float value) { if (value != 0) return Vec4(vec.x / value, vec.y / value, vec.z / value, vec.w / value); }

inline float dot(const Vec4 &vec1, const Vec4 &vec2) { return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w); }
//inline Vec4 cross(const Vec4 &vec1, const Vec4 &vec2, const Vec4 &vec3) {}//不需要

#endif//endif VEC4


