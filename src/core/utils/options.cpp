#include "options.h"

namespace snowrt {
namespace options {

#ifdef USING_DOUBLE_PRECISION
Float MinShadowBias = 1e-10;
Float MaxShadowBias = 1e-3;
Float ScaleShadowBias = 1e-8;
#else
Float MinShadowBias = 1e-8;
Float MaxShadowBias = 1e-1;
Float ScaleShadowBias = 1e-6;
#endif

}
}