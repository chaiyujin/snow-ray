#include "random.h"

namespace snowrt {
namespace random {

std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_real_distribution<Float> dis(0, 1);

Float uniform() { return dis(gen); }

}
}