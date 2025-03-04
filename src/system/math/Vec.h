#ifndef MATH_VEC_H
#define MATH_VEC_H
#include "utl/BinStream.h"

class Vector2 {
public:
    Vector2(){}
    Vector2(float xx, float yy) : x(xx), y(yy) {}
    void Set(float xx, float yy){ x = xx; y = yy; }
    float x;
    float y;
};

inline BinStream& operator>>(BinStream& bs, Vector2& vec){
    bs >> vec.x >> vec.y;
    return bs;
}

class Vector3 {
public:
    static Vector3 sX;
    static Vector3 sY;
    static Vector3 sZ;
    static Vector3 sZero;

    float x;
    float y;
    float z;

    Vector3(){}
    Vector3(float f1, float f2, float f3) : x(f1), y(f2), z(f3) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    void Set(float f1, float f2, float f3){ x = f1; y = f2; z = f3; }
    void Zero(){ x = y = z = 0.0f; }

    float X(){ return x; }
    float Y(){ return y; }
    float Z(){ return z; }
    
    Vector3& operator=(const Vector3& v){
        x = v.x; y = v.y; z = v.z;
        return *this;
    }

    Vector3& operator+=(const Vector3& v){
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& v){
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector3& operator*=(float f){
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    Vector3& operator/=(float f){
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }

    // float& operator[](int i){ return this + i; }
    // bool operator==(const Vector3 &) const;
    // bool operator!=(const Vector3 &) const;
};

inline BinStream& operator>>(BinStream& bs, Vector3& vec){
    bs >> vec.x >> vec.y >> vec.z;
    return bs;
}

class Vector4 {
public:
    static Vector4 sX;
    static Vector4 sY;
    static Vector4 sZ;
    static Vector4 sW;
    static Vector4 sZero;
    float x;
    float y;
    float z;
    float w;

    Vector4(float f1, float f2, float f3, float f4) : x(f1), y(f2), z(f3), w(f4) {}

    // Vector4(const Vector4 &);
};

class Vector4_16_01 {
    public:
    //Vector4_16_01() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    u16 x, y, z, w;
    float GetX() const { return (1.0f - x) / 65535.0;}
    float GetY() const; 
    float GetZ() const;
    void Set(float, float, float, float);
};

inline void Scale(const Vector3 &v1, float f, Vector3 &dst) {
    dst.Set(v1.x * f, v1.y * f, v1.z * f);
}

#endif
