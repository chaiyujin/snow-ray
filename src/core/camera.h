#pragma once
#include "vec.h"
#include "film.h"
#include "ray.h"

namespace snowrt {

class Camera {
    Float3 mEye;
    Float3 mFront;
    Float3 mUp;
    Float3 mRight;
    Float  mFoV;    // Height field of view
    Float  mAspect; // W/H
    Float  mHeight;
    Float  mWidth;
    Float3 mCorner;
    
    void _adjust() {
        // adjust up
        mFront.normalize();
        mRight = Cross(mFront, mUp).normalized();
        mUp = Cross(mRight, mFront).normalized();
        // fov, height and width
        Float theta = mFoV * constants::Pi / 360;
        mHeight = std::tan(theta) * (Float)2.0;
        mWidth  = mAspect * mHeight;
        // corner
        mCorner = mEye + mFront
                - mRight * mWidth / 2
                - mUp * mHeight / 2;
    }
public:
    Camera() {}
    Camera(const Float3 &eye, const Float3 &lookAt, const Float3 &up, Float fov, Float aspect)
        : mEye(eye), mFront(lookAt-eye), mUp(up)
        , mFoV(fov), mAspect(aspect) {
        this->_adjust();
    }
    virtual ~Camera() {}

    Ray getRay(const Film &film, uint32_t x, uint32_t y) const {
        const auto &res = film.resolution();
        Float sx = (Float)x / (Float)res.x;
        Float sy = 1 - (Float)y / (Float)res.y;
        return Ray(
            mEye,
            mCorner + mRight * mWidth * sx + mUp * mHeight * sy
        );
    }

};

}