template <typename T>
inline Vec3<T>::Vec3() :
x(0),
y(0),
z(0)
{ }

template <typename T>
inline Vec3<T>::Vec3(T value) :
x(value),
y(value),
z(value)
{ }

template <typename T>
inline Vec3<T>::Vec3(T x, T y, T z) :
x(x),
y(y),
z(z)
{ }

template <typename T>
template <typename U>
inline Vec3<T>::Vec3(const Vec3<U>& vector) :
x(static_cast<T>(vector.x)),
y(static_cast<T>(vector.y)),
z(static_cast<T>(vector.z))
{ }

template <typename T>
Vec3<T> Vec3<T>::up(
        static_cast<T>(0.0),
        static_cast<T>(1.0),
        static_cast<T>(0.0));

template <typename T>
Vec3<T> Vec3<T>::down(
        static_cast<T>(0.0),
        static_cast<T>(-1.0),
        static_cast<T>(0.0));

template <typename T>
Vec3<T> Vec3<T>::right(
        static_cast<T>(1.0),
        static_cast<T>(0.0),
        static_cast<T>(0.0));

template <typename T>
Vec3<T> Vec3<T>::left(
        static_cast<T>(-1.0),
        static_cast<T>(0.0),
        static_cast<T>(0.0));

template <typename T>
Vec3<T> Vec3<T>::forward(
        static_cast<T>(0.0),
        static_cast<T>(0.0),
        static_cast<T>(1.0));

template <typename T>
Vec3<T> Vec3<T>::backward(
        static_cast<T>(0.0),
        static_cast<T>(0.0),
        static_cast<T>(-1.0));

template <typename T>
Vec3<T> Vec3<T>::zero(
        static_cast<T>(0.0),
        static_cast<T>(0.0),
        static_cast<T>(0.0));

template <typename T>
Vec3<T> Vec3<T>::unitX(
        static_cast<T>(1.0),
        static_cast<T>(0.0),
        static_cast<T>(0.0));

template <typename T>
Vec3<T> Vec3<T>::unitY(
        static_cast<T>(0.0),
        static_cast<T>(1.0),
        static_cast<T>(0.0));

template <typename T>
Vec3<T> Vec3<T>::unitZ(
        static_cast<T>(0.0),
        static_cast<T>(0.0),
        static_cast<T>(1.0));

template <typename T>
inline T Vec3<T>::length() const
{
    return static_cast<T>(sqrt(x * x + y * y + z * z));
}

template <typename T>
inline T Vec3<T>::lengthSquared() const
{
    return x * x + y * y + z * z;
}

template <typename T>
inline T Vec3<T>::distance(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    const T deltaX = vectorA.x - vectorB.x;
    const T deltaY = vectorA.y - vectorB.y;
    const T deltaZ = vectorA.z - vectorB.z;

    return static_cast<T>(sqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ)));
}

template <typename T>
inline T Vec3<T>::distance(const Vec3<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;

    return static_cast<T>(sqrt((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ)));
}

template <typename T>
inline T Vec3<T>::distanceSquared(const Vec3<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;

    return static_cast<T>((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ));
}

template <typename T>
inline T Vec3<T>::distanceSquared(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    const T deltaX = vectorA.x - vectorB.x;
    const T deltaY = vectorA.y - vectorB.y;
    const T deltaZ = vectorA.z - vectorB.z;

    return static_cast<T>((deltaX*deltaX) + (deltaY*deltaY) + (deltaZ*deltaZ));
}

template <typename T>
inline T Vec3<T>::dot(const Vec3<T>& other) const
{
    return (x * other.x) + (y * other.y) + (z * other.z);
}

template <typename T>
inline T Vec3<T>::dot(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    return (vectorA.x * vectorB.x) + (vectorA.y * vectorB.y) + (vectorA.z * vectorB.z);
}

template <typename T>
inline void Vec3<T>::normalize()
{
    const T l = static_cast<T>(1.0) / length();
    x *= l;
    y *= l;
    z *= l;
}

template <typename T>
inline Vec3<T> Vec3<T>::normalize(const Vec3<T>& vector)
{
    const T l = static_cast<T>(1.0) / vector.length();
    return Vec3<T>(vector.x * l,
                   vector.y * l,
                   vector.z * l);
}

template <typename T>
inline Vec3<T> Vec3<T>::cross(const Vec3<T>& other) const
{
    Vec3<T> result;
    result.x = (y * other.z) - (z * other.y);
    result.y = (z * other.x) - (x * other.z);
    result.z = (x * other.y) - (y * other.x);
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::cross(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    Vec3<T> result;
    result.x = (vectorA.y * vectorB.z) - (vectorA.z * vectorB.y);
    result.y = (vectorA.z * vectorB.x) - (vectorA.x * vectorB.z);
    result.z = (vectorA.x * vectorB.y) - (vectorA.y * vectorB.x);
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::reflect(const Vec3<T>& vector, const Vec3<T>& normal)
{
    const T dotProduct = (vector.x * normal.x) + (vector.y * normal.y) + (vector.z * normal.z);

    Vec3<T> result;
    result.x = vector.x - static_cast<T>(2.0) * dotProduct * normal.x;
    result.y = vector.y - static_cast<T>(2.0) * dotProduct * normal.y;
    result.z = vector.z - static_cast<T>(2.0) * dotProduct * normal.z;
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::min(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    Vec3<T> result;
    result.x = vectorA.x < vectorB.x ? vectorA.x : vectorB.x;
    result.y = vectorA.y < vectorB.y ? vectorA.y : vectorB.y;
    result.z = vectorA.z < vectorB.z ? vectorA.z : vectorB.z;
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::max(const Vec3<T>& vectorA, const Vec3<T>& vectorB)
{
    Vec3<T> result;
    result.x = vectorA.x > vectorB.x ? vectorA.x : vectorB.x;
    result.y = vectorA.y > vectorB.y ? vectorA.y : vectorB.y;
    result.z = vectorA.z > vectorB.z ? vectorA.z : vectorB.z;
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::clamp(const Vec3<T>& value, const Vec3<T>& min, const Vec3<T>& max)
{
    const T valueX = value.x;
    const T clampX = valueX > max.x ? max.x : valueX;
    const T resultX = clampX < min.x ? min.x : clampX;

    const T valueY = value.y;
    const T clampY = valueY > max.y ? max.y : valueY;
    const T resultY = clampY < min.y ? min.y : clampY;

    const T valueZ = value.z;
    const T clampZ = valueZ > max.z ? max.z : valueZ;
    const T resultZ = clampZ < min.z ? min.z : clampZ;

    Vec3<T> result;

    result.x = resultX;
    result.y = resultY;
    result.z = resultZ;

    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::lerp(const Vec3<T>& previous, const Vec3<T>& current, const T amount)
{
    Vec3<T> result;
    result.x = previous.x + (current.x - previous.x) * amount;
    result.y = previous.y + (current.y - previous.y) * amount;
    result.z = previous.z + (current.z - previous.z) * amount;
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::barycentric(const Vec3<T>& vertexA, const Vec3<T>& vertexB, const Vec3<T>& vertexC, const T weightA, const T weightB)
{
    Vec3<T> result;
    result.x = (vertexA.x + weightA * (vertexB.x - vertexA.x) + weightB * (vertexC.x - vertexA.x));
    result.y = (vertexA.y + weightA * (vertexB.y - vertexA.y) + weightB * (vertexC.y - vertexA.y));
    result.z = (vertexA.z + weightA * (vertexB.z - vertexA.z) + weightB * (vertexC.z - vertexA.z));
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::smoothStep(const Vec3<T>& previous, const Vec3<T>& current, T amount)
{
    amount = amount > static_cast<T>(1.0) ? static_cast<T>(1.0) : (amount < static_cast<T>(0.0) ? static_cast<T>(0.0) : amount);
    amount = (amount * amount * (static_cast<T>(3.0) - static_cast<T>(2.0) * amount));
    Vec3<T> result;
    result.x = previous.x + (current.x - previous.x) * amount;
    result.y = previous.y + (current.y - previous.y) * amount;
    result.z = previous.z + (current.z - previous.z) * amount;
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::catmullRom(const Vec3<T>& vertexA, const Vec3<T>& vertexB, const Vec3<T>& vertexC, const Vec3<T>& vertexD, const T amount)
{
    const T square = amount * amount;
    const T cube = amount * square;

    Vec3<T> result;

    const T half = static_cast<T>(0.5);
    const T dbl = static_cast<T>(2.0);
    const T five = static_cast<T>(5.0);
    const T four = static_cast<T>(4.0);
    const T three = static_cast<T>(3.0);

    result.x = (half * (dbl * vertexB.x + (-vertexA.x + vertexC.x) * amount + (dbl * vertexA.x - five * vertexB.x + four * vertexC.x - vertexD.x) * square + (-vertexA.x + three * vertexB.x - three * vertexC.x + vertexD.x) * cube));
    result.y = (half * (dbl * vertexB.y + (-vertexA.y + vertexC.y) * amount + (dbl * vertexA.y - five * vertexB.y + four * vertexC.y - vertexD.y) * square + (-vertexA.y + three * vertexB.y - three * vertexC.y + vertexD.y) * cube));
    result.z = (half * (dbl * vertexB.z + (-vertexA.z + vertexC.z) * amount + (dbl * vertexA.z - five * vertexB.z + four * vertexC.z - vertexD.z) * square + (-vertexA.z + three * vertexB.z - three * vertexC.z + vertexD.z) * cube));
    return result;
}

template <typename T>
inline Vec3<T> Vec3<T>::hermite(const Vec3<T>& vertexA, const Vec3<T>& tangentA, const Vec3<T>& vertexB, const Vec3<T>& tangentB, const T amount)
{
    const T one = static_cast<T>(1.0);
    const T two = static_cast<T>(2.0);
    const T three = static_cast<T>(3.0);

    const T square = amount * amount;
    const T cube = amount * square;
    const T h1 = (two * cube - three * square + one);
    const T h2 = (-two * cube + three * square);
    const T h3 = cube - two * square + amount;
    const T h4 = cube - square;
    Vec3<T> result;
    result.x = (vertexA.x * h1 + vertexB.x * h2 + tangentA.x * h3 + tangentB.x * h4);
    result.y = (vertexA.y * h1 + vertexB.y * h2 + tangentA.y * h3 + tangentB.y * h4);
    result.z = (vertexA.z * h1 + vertexB.z * h2 + tangentA.z * h3 + tangentB.z * h4);
    return result;
}

template <typename T>
inline Vec3<T> operator -(const Vec3<T>& right)
{
    return Vec3<T>(-right.x, -right.y, -right.z);
}

template <typename T>
inline Vec3<T>& operator +=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

template <typename T>
inline Vec3<T>& operator -=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}

template <typename T>
inline Vec3<T> operator +(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x + right.x,
                   left.y + right.y,
                   left.z + right.z);
}

template <typename T>
inline Vec3<T> operator -(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x - right.x,
                   left.y - right.y,
                   left.z - right.z);
}

template <typename T>
inline Vec3<T> operator *(const Vec3<T>& left, T right)
{
    return Vec3<T>(left.x * right,
                   left.y * right,
                   left.z * right);
}

template <typename T>
inline Vec3<T> operator *(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x * right.x,
                   left.y * right.y,
                   left.z * right.z);
}

template <typename T>
inline Vec3<T> operator *(T left, const Vec3<T>& right)
{
    return Vec3<T>(right.x * left,
                   right.y * left,
                   right.z * left);
}

template <typename T>
inline Vec3<T>& operator *=(Vec3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

template <typename T>
inline Vec3<T>& operator *=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x *= right.x;
    left.y *= right.y;
    left.z *= right.z;

    return left;
}

template <typename T>
inline Vec3<T> operator /(const Vec3<T>& left, const Vec3<T>& right)
{
    return Vec3<T>(left.x / right.x,
                   left.y / right.y,
                   left.z / right.z);
}

template <typename T>
inline Vec3<T> operator /(const Vec3<T>& left, T right)
{
    const T oneOver = static_cast<T>(1.0) / right;
    return Vec3<T>(left.x * oneOver,
                   left.y * oneOver,
                   left.z * oneOver);
}

template <typename T>
inline Vec3<T>& operator /=(Vec3<T>& left, T right)
{
    const T oneOver = static_cast<T>(1.0) / right;
    left.x *= oneOver;
    left.y *= oneOver;
    left.z *= oneOver;

    return left;
}

template <typename T>
inline Vec3<T>& operator /=(Vec3<T>& left, const Vec3<T>& right)
{
    left.x /= right.x;
    left.y /= right.y;
    left.z /= right.z;

    return left;
}

template <typename T>
inline bool operator ==(const Vec3<T>& left, const Vec3<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

template <typename T>
inline bool operator !=(const Vec3<T>& left, const Vec3<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}
