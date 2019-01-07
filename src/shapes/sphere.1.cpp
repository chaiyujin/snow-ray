#include "sphere.h"

namespace snowrt {

bool Sphere::intersect(const Ray& ray) const {Float phi;
    Float3 pHit;
    /* discriminant */
    Float3 oc = ray.origin() - mCenter;
    Float a = Dot(ray.direction(), ray.direction());
    Float b = Dot(ray.direction(), oc);
    Float c = Dot(oc, oc) - mRadius*mRadius;
    Float disc = b*b - a*c;
    if (disc <= 0) return false;
    return true;
}

bool Sphere::intersect(const Ray& ray, Float *tHitPtr, SurfaceInteraction *insectPtr) const {
    Float phi;
    Float3 pHit;
    /* discriminant */
    EFloat ox(ray.origin().x),    oy(ray.origin().y),    oz(ray.origin().z);
    EFloat dx(ray.direction().x), dy(ray.direction().y), dz(ray.direction().z);
    ox = ox - mCenter.x;
    oy = oy - mCenter.y;
    oz = oz - mCenter.z;
    EFloat A = dx*dx+dy*dy+dz*dz;
    EFloat B = (ox*dx+oy*dy+oz*dz)*2;
    EFloat C = ox*ox+oy*oy+oz*oz - EFloat(mRadius)*EFloat(mRadius);
    EFloat t0(0), t1(0);
    if (!Quadratic(A,B,C,&t0,&t1))
        return false;
    if (t0.upper() > *tHitPtr || t1.lower() <= 0)
        return false;
    EFloat tHit = t0;
    if (tHit.lower() <= 0) {
        tHit = t1;
        if (tHit.upper() > *tHitPtr)
            return false;
    }
    *tHitPtr = (Float)tHit;
    insectPtr->time = *tHitPtr;
    insectPtr->point = ray(*tHitPtr);
    insectPtr->normal = (insectPtr->point - mCenter).normalized();
    insectPtr->wo = -ray.direction();
    insectPtr->time = *tHitPtr;
    insectPtr->shape = this;
    if (Dot(insectPtr->normal, insectPtr->wo) < 0)
        insectPtr->normal = -insectPtr->normal;
    return true;
}


}