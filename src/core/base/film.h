#pragma once
#include "../utils/utils.h"
#include <string>

namespace snowrt {

class Film {
    UInt2   mRes;
    Float3 *mDataPtr;
public:
    Film() {}
    Film(const UInt2& resolution)
        : mRes(resolution)
        , mDataPtr(nullptr) {
        // alloc data
        mDataPtr = new Float3[mRes.x * mRes.y];
        this->clear();
    }
    virtual ~Film() { delete[] mDataPtr; }
    void save(std::string filename);

    void clear() { memset(mDataPtr, 0, sizeof(Float3)*mRes.x*mRes.y); }
    void update(const Float3 &rgb, uint32_t x, uint32_t y) { mDataPtr[y*mRes.x + x] += rgb; }
    const UInt2 &resolution() const { return mRes; }
    const Float aspect() const { return (Float)mRes.x / (Float)mRes.y; }
};

}