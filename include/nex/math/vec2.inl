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
inline Vec2<T> Vec2<T>::min(const Vec2<T>& left, const Vec2<T>& right)
{
    Vec2<T> result;
    result.x = left.x < right.x ? left.x : right.x;
    result.y = left.y < right.y ? left.y : right.y;
    return result;
}

template <typename T>
inline Vec2<T> Vec2<T>::max(const Vec2<T>& left, const Vec2<T>& right)
{
    Vec2<T> result;
    result.x = left.x > right.x ? left.x : right.x;
    result.y = left.y > right.y ? left.y : right.y;
    return result;
}

template <typename T>
inline Vec2<T> Vec2<T>::clamp(const Vec2<T>& value, const Vec2<T>& min, const Vec2<T>& max)
{
    const T valueX = value.x;
    const T clampX = valueX > max.x ? max.x : valueX;
    const T resultX = clampX < min.x ? min.x : clampX;

    const T valueY = value.y;
    const T clampY = valueY > max.y ? max.y : valueY;
    const T resultY = clampY < min.y ? min.y : clampY;

    return Vec2<T>(resultX, resultY);
}

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
inline Vec2<T> Vec2<T>::reflect(const Vec2<T>& vector, const Vec2<T>& normal)
{
    const T distance = (vector.x * normal.x) + (vector.y * normal.y);
    Vec2<T> result;
    result.x = vector.x - static_cast<T>(2.0) * distance * normal.x;
    result.y = vector.y - static_cast<T>(2.0) * distance * normal.y;
    return result;
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
inline Vec2<T> Vec2<T>::lerp(const Vec2<T>& previous, const Vec2<T>& current, const T amount)
{
    Vec2<T> result;
    result.x = previous.x + (current.x - previous.x) * amount;
    result.y = previous.y + (current.y - previous.y) * amount;
    return result;
}

template <typename T>
inline Vec2<T> Vec2<T>::barycentric(const Vec2<T>& vertexA, const Vec2<T>& vertexB, const Vec2<T>& vertexC, const T weightA, const T weightB)
{
    Vec2<T> result;
    result.X = (vertexA.X + weightA * (vertexB.X - vertexA.X) + weightB * (vertexC.X - vertexA.X));
    result.Y = (vertexA.Y + weightA * (vertexB.Y - vertexA.Y) + weightB * (vertexC.Y - vertexA.Y));
    return result;
}

template <typename T>
inline Vec2<T> Vec2<T>::smoothStep(const Vec2<T>& previous, const Vec2<T>& current, T amount)
{
    amount =  amount > static_cast<T>(1.0) ? static_cast<T>(1.0): (amount < static_cast<T>(0.0) ? static_cast<T>(0.0) : amount);
    amount = (amount * amount * (static_cast<T>(3.0) - static_cast<T>(2.0) * amount));

    Vec2<T> result;
    result.x = previous.x + (current.x - previous.x) * amount;
    result.y = previous.y + (current.y - previous.y) * amount;
    return result;
}

template <typename T>
inline Vec2<T> Vec2<T>::catmullRom(const Vec2<T>& vertexA, const Vec2<T>& vertexB,
                                   const Vec2<T>& vertexC, const Vec2<T>& vertexD, const T amount)
{
    const T square = amount * amount;
    const T cube = amount * square;

    Vec2<T> result;

    result.X = (static_cast<T>(0.5) * (static_cast<T>(2.0) * vertexB.X + (-vertexA.X + vertexC.X) * amount +
                       (static_cast<T>(2.0) * vertexA.X - static_cast<T>(5.0) * vertexB.X + static_cast<T>(4.0) * vertexC.X - vertexD.X) * square +
                       (- vertexA.X + static_cast<T>(3.0) * vertexB.X - static_cast<T>(3.0) * vertexC.X + vertexD.X) * cube));
    result.Y = (static_cast<T>(0.5) * (static_cast<T>(2.0) * vertexB.Y + (-vertexA.Y + vertexC.Y) * amount +
                       (static_cast<T>(2.0) * vertexA.Y - static_cast<T>(5.0) * vertexB.Y + static_cast<T>(4.0) * vertexC.Y - vertexD.Y) * square +
                       (- vertexA.Y + static_cast<T>(3.0) * vertexB.Y - static_cast<T>(3.0) * vertexC.Y + vertexD.Y) * cube));
    return result;
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
