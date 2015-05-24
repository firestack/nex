#include <cmath>

template <typename T>
inline Vec2<T>::Vec2() :
x(0),
y(0)
{ }

template <typename T>
inline Vec2<T>::Vec2(T value) :
x(value),
y(value)
{ }

template <typename T>
inline Vec2<T>::Vec2(T x, T y) :
x(x),
y(y)
{ }

template <typename T>
template <typename U>
inline Vec2<T>::Vec2(const Vec2<U>& vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y))
{ }

template <typename T>
inline void Vec2<T>::normalize()
{
    const T l = static_cast<T>(1.0) / length();
    x *= l;
    y *= l;
}

template <typename T>
inline Vec2<T> Vec2<T>::normalize(const Vec2<T>& value)
{
    const T l = static_cast<T>(1.0) / value.length();

    return Vec2<T>(value.x * l,
                   value.y * l);
}

template <typename T>
inline T Vec2<T>::length() const
{
    return static_cast<T>(std::sqrt(lengthSquared()));
}

template <typename T>
inline T Vec2<T>::lengthSquared() const
{
    return static_cast<T>((x * x) + (y * y));
}

template <typename T>
inline T Vec2<T>::distance(const Vec2<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;

    return static_cast<T>(std::sqrt((deltaX * deltaX) + (deltaY * deltaY)));
}

template <typename T>
inline T Vec2<T>::distance(const Vec2<T>& left, const Vec2<T>& right)
{
    const T deltaX = left.x - right.x;
    const T deltaY = left.y - right.y;

    return static_cast<T>(std::sqrt((deltaX * deltaX) + (deltaY * deltaY)));
}

template <typename T>
inline T Vec2<T>::distanceSquared(const Vec2<T>& left, const Vec2<T>& right)
{
    const T deltaX = left.x - right.x;
    const T deltaY = left.y - left.y;

    return static_cast<T>((deltaX * deltaX) + (deltaY * deltaY));
}

template <typename T>
inline T Vec2<T>::distanceSquared(const Vec2<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;

    return static_cast<T>((deltaX * deltaX) + (deltaY * deltaY));
}

template <typename T>
inline T Vec2<T>::dot(const Vec2<T>& left, const Vec2<T>& right)
{
    return (left.x * right.x) + (left.y * right.y);
}

template <typename T>
inline T Vec2<T>::dot(const Vec2<T>& other)
{
    return x * other.x + y * other.y;
}

template <typename T>
inline Vec2<T> operator -(const Vec2<T>& right)
{
    return Vec2<T>(-right.x, -right.y);
}

template <typename T>
inline Vec2<T>& operator +=(Vec2<T>& left, const Vec2<T>& right)
{
    left.x += right.x;
    left.y += right.y;

    return left;
}

template <typename T>
inline Vec2<T>& operator -=(Vec2<T>& left, const Vec2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;

    return left;
}

template <typename T>
inline Vec2<T> operator +(const Vec2<T>& left, const Vec2<T>& right)
{
    return Vec2<T>(left.x + right.x,
                   left.y + right.y);
}

template <typename T>
inline Vec2<T> operator -(const Vec2<T>& left, const Vec2<T>& right)
{
    return Vec2<T>(left.x - right.x,
                   left.y - right.y);
}

template <typename T>
inline Vec2<T> operator *(const Vec2<T>& left, T right)
{
    return Vec2<T>(left.x * right,
                   left.y * right);
}

template <typename T>
inline Vec2<T> operator *(T left, const Vec2<T>& right)
{
    return Vec2<T>(right.x * left,
                   right.y * left);
}

template <typename T>
inline Vec2<T>& operator *=(Vec2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;

    return left;
}

template <typename T>
inline Vec2<T> operator /(const Vec2<T>& left, T right)
{
    return Vec2<T>(left.x / right,
                   left.y / right);
}

template <typename T>
inline Vec2<T>& operator /=(Vec2<T>& left, T right)
{
    left.x /= right;
    left.y /= right;

    return left;
}

template <typename T>
inline bool operator ==(const Vec2<T>& left, const Vec2<T>& right)
{
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator !=(const Vec2<T>& left, const Vec2<T>& right)
{
    return (left.x != right.x) || (left.y != right.y);
}
