#ifndef GJK_H_INCLUDE
#define GJK_H_INCLUDE

#include <nex/math/vec3.h>

namespace nx
{

/**
 * @brief The GJK class, does magic voodoo.
 */
class GJK
{
public:
    GJK();

    bool fullSimplex() const { return mSimplexBits == 15; }

    float maxLengthSquared() const { return mMaxLengthSq; }

    vec3f closestPoint() const { return mClosestPoint; }

    bool addSupportPoint(const vec3f& newPoint);

    void reset();

private:

    int mSimplexBits;
    float mMaxLengthSq;

    vec3f mClosestPoint;

    vec3f mY[4];
    float mYLengthSq[4];

    vec3f mEdges[4][4];
    float mEdgeLengthSq[4][4];

    float mDet[16][4];

    int mBitsToIndices[16];

    void updateDeterminant(int xmIdx);
    bool updateSimplex(int newIndex);
    vec3f computeClosestPoint();
    bool satisfiesRule(int xBits, int yBits);
}; //namespace GJK
} //namespace nx

#endif
