template <typename T>
inline Vec4<T>::Vec4() :
    x(0),
    y(0),
    z(0),
    w(0)
{ }

template <typename T>
inline Vec4<T>::Vec4(T value) :
    x(value),
    y(value),
    z(value),
    w(value)
{ }

template <typename T>
inline Vec4<T>::Vec4(T x, T y, T z, T w) :
    x(x),
    y(y),
    z(z),
    w(w)
{ }

template <typename T>
template <typename U>
inline Vec4<T>::Vec4(const Vec4<U>& vector) :
    x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y)),
    z(static_cast<T>(vector.z)),
    w(static_cast<T>(vector.w))
{ }


template <typename T>
inline T Vec4<T>::length() const
{
    return static_cast<T>(sqrt((x * x) + (y * y) +  (z * z) +  (w * w)));
}

template <typename T>
inline T Vec4<T>::lengthSquared() const
{
    return (x * x) + (y * y) +  (z * z) +  (w * w);
}

template <typename T>
inline T Vec4<T>::distance(const Vec4<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;
    const T deltaW = w - other.w;

    return sqrtf(
                (deltaX * deltaX) +
                (deltaY * deltaY) +
                (deltaZ * deltaZ) +
                (deltaW * deltaW));
}

template <typename T>
inline T Vec4<T>::distanceSquared(const Vec4<T>& other) const
{
    const T deltaX = x - other.x;
    const T deltaY = y - other.y;
    const T deltaZ = z - other.z;
    const T deltaW = w - other.w;

    return (deltaX * deltaX) +
           (deltaY * deltaY) +
           (deltaZ * deltaZ) +
           (deltaW * deltaW);
}

template <typename T>
inline T Vec4<T>::dot(const Vec4<T>& other) const
{
    return (x * other.x) +
           (y * other.y) +
           (z * other.z) +
           (w * other.w);
}

template <typename T>
inline void Vec4<T>::normalize()
{
  const T oneOverLength = 1.0f / length();
  x *= oneOverLength;
  y *= oneOverLength;
  z *= oneOverLength;
  w *= oneOverLength;
}

template <typename T>
inline T Vec4<T>::distance(const Vec4<T>& left, const Vec4<T>& right)
{
    const T deltaX = left.x - right.x;
    const T deltaY = left.y - right.y;
    const T deltaZ = left.z - right.z;
    const T deltaW = left.w - right.w;

    return sqrtf(
                (deltaX * deltaX) +
                (deltaY * deltaY) +
                (deltaZ * deltaZ) +
                (deltaW * deltaW));
}

template <typename T>
inline T Vec4<T>::distanceSquared(const Vec4<T>& left, const Vec4<T>& right)
{
    const T deltaX = left.x - right.x;
    const T deltaY = left.y - right.y;
    const T deltaZ = left.z - right.z;
    const T deltaW = left.w - right.w;

    return (deltaX * deltaX) +
           (deltaY * deltaY) +
           (deltaZ * deltaZ) +
           (deltaW * deltaW);
}

template <typename T>
inline T Vec4<T>::dot(const Vec4<T>& left, const Vec4<T>& right)
{
    return (left.x * right.x) +
           (left.y * right.y) +
           (left.z * right.z) +
           (left.w * right.w);
}

template <typename T>
inline Vec4<T> Vec4<T>::normalize(const Vec4<T>& value)
{
    const T oneOverLength = 1.0f / value.length();

    Vec4<T> result;

    result.x *= oneOverLength;
    result.y *= oneOverLength;
    result.z *= oneOverLength;
    result.w *= oneOverLength;

    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::min(const Vec4<T>& left, const Vec4<T>& right)
{
    Vec4<T> result;
    result.x = left.x < right.x ? left.x : right.x;
    result.y = left.y < right.y ? left.y : right.y;
    result.z = left.z < right.z ? left.z : right.z;
    result.w = left.w < right.w ? left.w : right.w;
    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::max(const Vec4<T>& left, const Vec4<T>& right)
{
    Vec4<T> result;
    result.x = left.x > right.x ? left.x : right.x;
    result.y = left.y > right.y ? left.y : right.y;
    result.z = left.z > right.z ? left.z : right.z;
    result.w = left.w > right.w ? left.w : right.w;
    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::clamp(const Vec4<T>& value, const Vec4<T>& min, const Vec4<T>& max)
{
    const float valueX = value.x;
    const float minX = valueX > max.x ? max.x : valueX;
    const float resultX =  minX < min.x ? min.x : minX;

    const float valueY = value.y;
    const float minY = valueY > max.y ? max.y : valueY;
    const float resultY =  minY < min.y ? min.y : minY;

    const float valueZ = value.z;
    const float minZ = valueZ > max.z ? max.z : valueZ;
    const float resultZ = minZ < min.z ? min.z : minZ;

    const float valueW = value.w;
    const float minW = valueW > max.w ? max.w : valueW;
    const float resultW = minW < min.w ? min.w : minW;

    Vec4<T> result;
    result.x = resultX;
    result.y = resultY;
    result.z = resultZ;
    result.w = resultW;
    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::lerp(const Vec4<T>& previous, const Vec4<T>& current, const T amount)
{
    Vec4<T> result;
    result.x = previous.x + (current.x - previous.x) * amount;
    result.y = previous.y + (current.y - previous.y) * amount;
    result.z = previous.z + (current.z - previous.z) * amount;
    result.w = previous.w + (current.w - previous.w) * amount;
    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::barycentric(
        const Vec4<T>& vertexA,
        const Vec4<T>& vertexB,
        const Vec4<T>& vertexC, const T weightA, const T weightB)
{
    Vec4<T> result;
    result.x = (vertexA.x + weightA * (vertexB.x - vertexA.x) + weightB * (vertexC.x - vertexA.x));
    result.y = (vertexA.y + weightA * (vertexB.y - vertexA.y) + weightB * (vertexC.y - vertexA.y));
    result.z = (vertexA.z + weightA * (vertexB.z - vertexA.z) + weightB * (vertexC.z - vertexA.z));
    result.w = (vertexA.w + weightA * (vertexB.w - vertexA.w) + weightB * (vertexC.w - vertexA.w));
    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::smoothStep(const Vec4<T>& previous, const Vec4<T>& current, T amount)
{
    const T zero = static_cast<T>(0.0);
    const T one = static_cast<T>(1.0);
    const T two = static_cast<T>(2.0);
    const T three = static_cast<T>(3.0);

    amount = amount > one ? one : (amount < zero ? zero : amount);
    amount = (amount * amount * (three - two * amount));

    Vec4<T> result;

    result.x = previous.x + (current.x - previous.x) * amount;
    result.y = previous.y + (current.y - previous.y) * amount;
    result.z = previous.z + (current.z - previous.z) * amount;
    result.w = previous.w + (current.w - previous.w) * amount;

    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::catmullRom(
        const Vec4<T>& vertexA,
        const Vec4<T>& vertexB,
        const Vec4<T>& vertexC,
        const Vec4<T>& vertexD,
        const T weight)
{
    const T squared = weight * weight;
    const T cubed = weight * squared;

    Vec4<T> result;

    const T half = static_cast<T>(0.5);
    const T db = static_cast<T>(2.0);
    const T th = static_cast<T>(3.0);
    const T qd = static_cast<T>(4.0);
    const T ft = static_cast<T>(5.0);

    result.x = (half * (db * vertexB.x + (-vertexA.x + vertexC.x) * weight + (db * vertexA.x - ft * vertexB.x + qd * vertexC.x - vertexD.x) * squared + (-vertexA.x + th * vertexB.x - th * vertexC.x + vertexD.x) * cubed));
    result.y = (half * (db * vertexB.y + (-vertexA.y + vertexC.y) * weight + (db * vertexA.y - ft * vertexB.y + qd * vertexC.y - vertexD.y) * squared + (-vertexA.y + th * vertexB.y - th * vertexC.y + vertexD.y) * cubed));
    result.z = (half * (db * vertexB.z + (-vertexA.z + vertexC.z) * weight + (db * vertexA.z - ft * vertexB.z + qd * vertexC.z - vertexD.z) * squared + (-vertexA.z + th * vertexB.z - th * vertexC.z + vertexD.z) * cubed));
    result.w = (half * (db * vertexB.w + (-vertexA.w + vertexC.w) * weight + (db * vertexA.w - ft * vertexB.w + qd * vertexC.w - vertexD.w) * squared + (-vertexA.w + th * vertexB.w - th * vertexC.w + vertexD.w) * cubed));

    return result;
}

template <typename T>
inline Vec4<T> Vec4<T>::hermite(
        const Vec4<T>& vertexA,
        const Vec4<T>& tangentA,
        const Vec4<T>& vertexB,
        const Vec4<T>& tangentB,
        const T weight)
{
    const T one = static_cast<T>(1.0);
    const T two = static_cast<T>(2.0);
    const T three = static_cast<T>(3.0);

    const T weightSquared = weight * weight;
    const T weightCubed = weight * weightSquared;
    const T h1 = (two * weightCubed - three * weightSquared + one);
    const T h2 = (-two * weightCubed + three * weightSquared);
    const T h3 = weightCubed - two * weightSquared + weight;
    const T h4 = weightCubed - weightSquared;

    Vec4<T> result;

    result.x = (vertexA.x * h1 + vertexB.x * h2 + tangentA.x * h3 + tangentB.x * h4);
    result.y = (vertexA.y * h1 + vertexB.y * h2 + tangentA.y * h3 + tangentB.y * h4);
    result.z = (vertexA.z * h1 + vertexB.z * h2 + tangentA.z * h3 + tangentB.z * h4);
    result.w = (vertexA.w * h1 + vertexB.w * h2 + tangentA.w * h3 + tangentB.w * h4);

    return result;
}

template <typename T>
inline Vec4<T> operator -(const Vec4<T>& right)
{
    return Vec4<T>(-right.x, -right.y, -right.z, -right.w);
}

template <typename T>
inline Vec4<T> operator +(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x + right.x,
                   left.y + right.y,
                   left.z + right.z,
                   left.w + right.w);
}

template <typename T>
inline Vec4<T>& operator +=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    left.w += right.w;

    return left;
}

template <typename T>
inline Vec4<T> operator -(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x - right.x,
                   left.y - right.y,
                   left.z - right.z,
                   left.w - right.w);
}

template <typename T>
inline Vec4<T>& operator -=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    left.w -= right.z;

    return left;
}

template <typename T>
inline Vec4<T> operator *(const Vec4<T>& left, const T right)
{
    return Vec4<T>(left.x * right,
                   left.y * right,
                   left.z * right,
                   left.w * right);
}

template <typename T>
inline Vec4<T> operator *(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x * right.x,
                   left.y * right.y,
                   left.z * right.z,
                   left.w * right.w);
}

template <typename T>
inline Vec4<T> operator *(const T left, const Vec4<T>& right)
{
    return Vec4<T>(right.x * left,
                   right.y * left,
                   right.z * left,
                   right.w * left);
}

template <typename T>
inline Vec4<T>& operator *=(Vec4<T>& left, const T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;
    left.w *= right;

    return left;
}

template <typename T>
inline Vec4<T>& operator *=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x *= right.x;
    left.y *= right.y;
    left.z *= right.z;
    left.w *= right.w;

    return left;
}

template <typename T>
inline Vec4<T> operator /(const Vec4<T>& left, const Vec4<T>& right)
{
    return Vec4<T>(left.x / right.x,
                   left.y / right.y,
                   left.z / right.z,
                   left.w / right.w);
}

template <typename T>
inline Vec4<T> operator /(const Vec4<T>& left, const T right)
{
    const T oneOver = static_cast<T>(1.0) / right;
    return Vec4<T>(left.x * oneOver,
                   left.y * oneOver,
                   left.z * oneOver,
                   left.w * oneOver);
}

template <typename T>
inline Vec4<T>& operator /=(Vec4<T>& left, const T right)
{
    const T oneOver = static_cast<T>(1.0) / right;

    left.x *= oneOver;
    left.y *= oneOver;
    left.z *= oneOver;
    left.w *= oneOver;

    return left;
}

template <typename T>
inline Vec4<T>& operator /=(Vec4<T>& left, const Vec4<T>& right)
{
    left.x /= right.x;
    left.y /= right.y;
    left.z /= right.z;
    left.w /= right.w;

    return left;
}

template <typename T>
inline bool operator ==(const Vec4<T>& left, const Vec4<T>& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z) && (left.w == right.w);
}

template <typename T>
inline bool operator !=(const Vec4<T>& left, const Vec4<T>& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z) || (left.w != right.w);
}
