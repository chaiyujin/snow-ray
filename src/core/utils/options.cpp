#include "options.h"

namespace snowrt {
namespace options {

#ifdef USING_DOUBLE_PRECISION
Float MinShadowEps = 1e-10;
Float MaxShadowEps = 1e-3;
Float ScaleShadowEps = 1e-8;
#else
Float MinShadowEps = 1e-8;
Float MaxShadowEps = 1e-1;
Float ScaleShadowEps = 1e-6;
#endif

}
}