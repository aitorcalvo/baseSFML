#include <math.h>
#include "vector.h"

/*
 * \brief Calculate the dot product of two 2D vectors
 */
int DotProduct2D (const struct Vector2D * _a, const struct Vector2D * _b) {
    return _a->x*_b->x + _a->y*_b->y;
}


/*
 * \brief Check if the origin->B vector is to the right of the origin->A vector
 */
bool IsRightSide (const struct Vector2D * _origin, const struct Vector2D * _a, const struct Vector2D * _b) {
    /* Rotate 90 degrees the origin->a vector to produce the expected result */
    struct Vector2D o_a = {-(_a->y - _origin->y), _a->x - _origin->x};
    struct Vector2D o_b = {_b->x - _origin->x, _b->y - _origin->y};
    return DotProduct2D (&o_a, &o_b) >= 0;
}

/*
 * \brief Calculate the dot product of two 3D vectors
 */
double DotProduct3D (const struct Vector3D * _a, const struct Vector3D * _b) {
    return _a->x*_b->x + _a->y*_b->y + _a->z*_b->z;
}

/*
 * \brief Modulo of a 3D vector
 */
double Modulo3D (const struct Vector3D * _v) {
    return sqrt (_v->x*_v->x + _v->y*_v->y + _v->z*_v->z);
}

/*
 * \brief Normalize a 3D vector so that it has modulo 1
 * \return Modulo of the original vector, in case needed to avoid recalculation
 */
double Normalize3D (struct Vector3D * _v) {
    double fModulo = Modulo3D (_v);
    _v->x /= fModulo;
    _v->y /= fModulo;
    _v->z /= fModulo;

    return fModulo;
}

/*
 * \brief Cross product => x = a x b
 */
void CrossProduct3D (struct Vector3D * _x, const struct Vector3D * _a, const struct Vector3D * _b) {
    _x->x = _a->y * _b->z - _a->z * _b->y;
    _x->y = -(_a->x * _b->z - _a->z * _b->x);
    _x->z = _a->x * _b->y - _a->y * _b->x;
}

/*
 * \brief Rotate a 3D vector given its axis
 * \details The function maintains the original modulo of the vector
 * The resulting vector is basically r*|v| = cos(theta) * v + sin(theta) * (v x a),
 * where both v and a have been previously normalized
 */
void Rotate3D (struct Vector3D * _rotated, const struct Vector3D * _v, const struct Vector3D * _axis, double _theta) {
    /* Normalize all to have a unitary basis */
    struct Vector3D norm_v = *_v;
    double fModulo = Normalize3D (&norm_v);
    struct Vector3D norm_axis = *_axis;
    (void) Normalize3D (&norm_axis);

    /* Cross product v x axis and v form the rotation plane */
    struct Vector3D cross;
    CrossProduct3D (&cross, &norm_v, &norm_axis);

    /* Apply the rotation: r = v * cos(theta) + (v x a) * sin(theta) */
    /* Also restore original modulo */
    _rotated->x = fModulo * (norm_v.x * cos(_theta) + cross.x * sin(_theta));
    _rotated->y = fModulo * (norm_v.y * cos(_theta) + cross.y * sin(_theta));
    _rotated->z = fModulo * (norm_v.z * cos(_theta) + cross.z * sin(_theta));
}
