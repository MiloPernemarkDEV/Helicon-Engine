#include "mat4x4.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Mat4x4& a)
{
    out << a.m11 << ' ' << a.m12 << ' ' << a.m13 << ' ' << a.m14 << '\n'
        << a.m21 << ' ' << a.m22 << ' ' << a.m23 << ' ' << a.m24 << '\n'
        << a.m31 << ' ' << a.m32 << ' ' << a.m33 << ' ' << a.m34 << '\n'
        << a.m41 << ' ' << a.m42 << ' ' << a.m43 << ' ' << a.m44;

    return out;
}
