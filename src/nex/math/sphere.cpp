#include <nex/math/sphere.h>
#include <nex/math/aabb.h>
#include <nex/math/frustum.h>

namespace nx
{

Sphere::Sphere() :
    center(vec3f()),
    radius(0.0f)
{ }

Sphere::Sphere(const vec3f center, const float radius) :
    center(center),
    radius(radius)
{ }

bool Sphere::intersects(const Sphere& sphere) const
{
    const float distanceSquared = vec3f::distanceSquared(center, sphere.center);
    return (radius * radius) + (2.0f * radius * sphere.radius) + (sphere.radius * sphere.radius) > distanceSquared;
}

bool Sphere::intersects(const AABB& box) const
{
    const vec3f clampedResult = vec3f::clamp(center, box.min, box.max);
    const float distanceSquared = vec3f::distanceSquared(center, clampedResult);
    return distanceSquared <= (radius * radius);
}

ContainmentType Sphere::contains(const AABB& box) const
{
    if (!box.intersects(*this))
        return ContainmentType::Disjoint;

    const float radiusSquared = radius * radius;

    vec3f test;
    test.x = center.x - box.min.x;
    test.y = center.y - box.max.y;
    test.z = center.z - box.max.z;

    if (test.lengthSquared() > radiusSquared)
        return ContainmentType::Intersects;

    test.x = center.x - box.max.x;
    test.y = center.y - box.max.y;
    test.z = center.z - box.max.z;

    if (test.lengthSquared() > radiusSquared)
        return ContainmentType::Intersects;

    test.x = center.x - box.max.x;
    test.y = center.y - box.min.y;
    test.z = center.z - box.max.z;

    if (test.lengthSquared() > radiusSquared)
        return ContainmentType::Intersects;

    test.x = center.x - box.min.x;
    test.y = center.y - box.min.y;
    test.z = center.z - box.max.z;

    if (test.lengthSquared() > radiusSquared)
        return ContainmentType::Intersects;

    test.x = center.x - box.min.x;
    test.y = center.y - box.max.y;
    test.z = center.z - box.min.z;

    if (test.lengthSquared() > radiusSquared)
        return ContainmentType::Intersects;

    test.x = center.x - box.max.x;
    test.y = center.y - box.max.y;
    test.z = center.z - box.min.z;

    if (test.lengthSquared() > radiusSquared)
        return ContainmentType::Intersects;

    test.x = center.x - box.max.x;
    test.y = center.y - box.min.y;
    test.z = center.z - box.min.z;

    if (test.lengthSquared() > radiusSquared)
        return ContainmentType::Intersects;

    test.x = center.x - box.min.x;
    test.y = center.y - box.min.y;
    test.z = center.z - box.min.z;

    return test.lengthSquared() > radiusSquared ? ContainmentType::Intersects : ContainmentType::Contains;
}

ContainmentType Sphere::contains(const Frustum& frustum) const
{
    if (!frustum.intersects(*this))
        return ContainmentType::Disjoint;

    const float radiusSquared = radius * radius;
    const vec3f* array = frustum.getCorners();

    for (int i = 0; i < 8; i++)
    {
        if ((array[i] - center).lengthSquared() > radiusSquared)
            return ContainmentType::Intersects;
    }

    return ContainmentType::Contains;
}

ContainmentType Sphere::contains(const vec3f& point) const
{
    return vec3f::distanceSquared(point, center) >= (radius * radius) ? ContainmentType::Disjoint : ContainmentType::Contains;
}

ContainmentType Sphere::contains(const Sphere& sphere) const
{
    const float result = vec3f::distance(center, sphere.center);

    if (radius + sphere.radius < result)
        return ContainmentType::Disjoint;

    return radius - sphere.radius < result ? ContainmentType::Intersects : ContainmentType::Contains;
}

Sphere Sphere::createMerged(const Sphere& original, const Sphere& additional)
{
    const vec3f result = additional.center - original.center;
    const float resultLength = result.length();
    const float radiusA = original.radius;
    const float radiusB = additional.radius;

    if (radiusA + radiusB >= resultLength)
    {
        if (radiusA - radiusB >= resultLength)
            return original;
        if (radiusB - radiusA >= resultLength)
            return additional;
    }

    const vec3f oneOverLength = result * (1.0f / resultLength);

    const float minRad = min(-radiusA, resultLength - radiusB);
    const float maxRad = ((max(radiusA, resultLength + radiusB) - minRad) * 0.5f);

    Sphere resultSphere;

    resultSphere.center = original.center + oneOverLength * (maxRad + minRad);
    resultSphere.radius = maxRad;

    return resultSphere;
}

Sphere Sphere::createFromBoundingBox(const AABB& box)
{
    Sphere boundingSphere;
    boundingSphere.center = vec3f::lerp(box.min, box.max, 0.5f);

    const float resultRadius = vec3f::distance(box.max, box.max);
    boundingSphere.radius = resultRadius * 0.5f;
    return boundingSphere;
}

Sphere Sphere::createFromPoints(std::vector<vec3f> points)
{
    if (points.size() == 0)
        return Sphere();

    vec3f current = points.at(0);
    //min y
    vec3f resultA = current;
    //max y
    vec3f resultB = current;
    //min x
    vec3f resultC = current;
    //max x
    vec3f resultD = current;
    //min z
    vec3f resultF = current;
    //max z
    vec3f resultG = current;

    for (auto& point : points)
    {
        if (point.x < resultG.x)
            resultG = point;
        if (point.x > resultF.x)
            resultF = point;
        if (point.y < resultD.y)
            resultD = point;
        if (point.y > resultC.y)
            resultC = point;
        if (point.z < resultB.z)
        resultB = point;
        if (point.z > resultA.z)
            resultA = point;
    }

    float result1 = vec3f::distance(resultF, resultG);
    float result2 = vec3f::distance(resultC, resultD);
    float result3 = vec3f::distance(resultA, resultB);

    vec3f resultCenter;

    float resultRadius;

    if (result1 > result2)
    {
        if (result1 > result3)
        {
            resultCenter = vec3f::lerp(resultF, resultG, 0.5f);
            resultRadius = result1 * 0.5f;
        }
        else
        {
            resultRadius = result3 * 0.5f;
            resultCenter = vec3f::lerp(resultA, resultB, 0.5f);
        }
    }
    else if (result2 > result3)
    {
        resultCenter = vec3f::lerp(resultC, resultD, 0.5f);
        resultRadius = result2 * 0.5f;
    }
    else
    {
        resultCenter = vec3f::lerp(resultA, resultB, 0.5f);
        resultRadius = result3 * 0.5f;
    }

    for (auto& pomint : points)
    {
        vec3f calc;
        calc.x = pomint.x - resultCenter.x;
        calc.y = pomint.y - resultCenter.y;
        calc.z = pomint.z - resultCenter.z;
        float length = calc.length();
        if (length > resultRadius)
        {
            resultRadius = ((resultRadius + length) * 0.5f);
            resultCenter += (1.0f - resultRadius / length) * calc;
        }
    }

    Sphere boundingSphere;
    boundingSphere.center = resultCenter;
    boundingSphere.radius = resultRadius;
    return boundingSphere;
}

} //namespace nx
