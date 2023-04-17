#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdbool.h>

struct Vector2D {
    int x;
    int y;
};

struct Vector3D {
    double x;
    double y;
    double z;
};

int DotProduct2D (const struct Vector2D * _a, const struct Vector2D * _b);
bool IsRightSide (const struct Vector2D * _origin, const struct Vector2D * _a, const struct Vector2D * _b);

double DotProduct3D (const struct Vector3D * _a, const struct Vector3D * _b);
double Modulo3D (const struct Vector3D * _v);
double Normalize3D (struct Vector3D * _v);
void CrossProduct3D (struct Vector3D * _x, const struct Vector3D * _a, const struct Vector3D * _b);
void Rotate3D (struct Vector3D * _rotated, const struct Vector3D * _v, const struct Vector3D * _axis, double _theta);

#endif //__VECTOR_H__

