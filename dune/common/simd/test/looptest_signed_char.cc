#include <config.h>

#include <dune/common/simd/test/looptest.hh>

namespace Dune {
  namespace Simd {

    template void UnitTest::checkVector<LoopSIMD<signed char, 5>>();

  } //namespace Simd
} // namespace Dune