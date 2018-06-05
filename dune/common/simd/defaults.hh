#ifndef DUNE_COMMON_SIMD_DEFAULTS_HH
#define DUNE_COMMON_SIMD_DEFAULTS_HH

/** @file
 *  @brief Default implementations for SIMD Implementations
 *  @ingroup SIMDAbstract
 *
 * This file provides default overloads for SIMD implementation functions, and
 * deleted placeholders where there are no default implementations.
 *
 * This file should never be included by users of the SIMD
 * abstraction. Include <dune/common/simd/simd.hh> instead.
 */

#include <cstddef>

#include <dune/common/rangeutilities.hh>
#include <dune/common/simd/base.hh>
#include <dune/common/simd/interface.hh>

namespace Dune {
  namespace Simd {
    namespace Overloads {

      /**
       * @addtogroup SIMDAbstract
       * @{
       */

      /** @name Overloadable and default functions
       *
       * This group contains functions that you, as an abstraction developer,
       * must implement.  All functions that are deleted must be provided,
       * functions that have a default implementation may be left
       * unimplemented if the default behaviour is satisfactory.
       *
       * @{
       */

      //! implements Simd::lane()
      template<class V>
      decltype(auto) lane(ADLTag<0>, std::size_t l, V v) = delete;

      //! implements Simd::cond()
      template<class V>
      V cond(ADLTag<0>, Mask<V> mask, V ifTrue, V ifFalse) = delete;

      //! implements Simd::anyTrue()
      template<class Mask>
      bool anyTrue(ADLTag<0>, Mask mask) = delete;

      //! implements Simd::allTrue()
      /**
       * Default uses Simd::anyTrue()
       */
      template<class Mask>
      bool allTrue(ADLTag<0>, Mask mask)
      {
        return !Dune::Simd::anyTrue(!mask);
      }

      //! implements Simd::anyFalse()
      /**
       * Default uses Simd::anyTrue()
       */
      template<class Mask>
      bool anyFalse(ADLTag<0>, Mask mask)
      {
        return Dune::Simd::anyTrue(!mask);
      }

      //! implements Simd::allFalse()
      /**
       * Default uses Simd::anyTrue()
       */
      template<class Mask>
      bool allFalse(ADLTag<0>, Mask mask)
      {
        return !Dune::Simd::anyTrue(mask);
      }

      //! implements Simd::maxValue()
      template<class V>
      auto max(ADLTag<0>, const V &v)
      {
        Scalar<V> m = Simd::lane(0, v);
        for(std::size_t l = 1; l < Simd::lanes(v); ++l)
          if(m < Simd::lane(l, v))
            m = Simd::lane(l, v);
        return m;
      }

      //! implements Simd::minValue()
      template<class V>
      auto min(ADLTag<0>, const V &v)
      {
        Scalar<V> m = Simd::lane(0, v);
        for(std::size_t l = 1; l < Simd::lanes(v); ++l)
          if(Simd::lane(l, v) < m)
            m = Simd::lane(l, v);
        return m;
      }

      //! implements Simd::mask()
      template<class V>
      Mask<V> mask(ADLTag<0, std::is_same<V, Mask<V> >::value>,
                   const V &v)
      {
        return v;
      }

      //! implements Simd::mask()
      template<class V>
      Mask<V> mask(ADLTag<0, !std::is_same<V, Mask<V> >::value>,
                   const V &v)
      {
        return v != V(Scalar<V>(0));
      }

      //! implements Simd::maskOr()
      template<class V1, class V2>
      auto maskOr(ADLTag<0>, const V1 &v1, const V2 &v2)
      {
        return Simd::mask(v1) || Simd::mask(v2);
      }

      //! implements Simd::maskAnd()
      template<class V1, class V2>
      auto maskAnd(ADLTag<0>, const V1 &v1, const V2 &v2)
      {
        return Simd::mask(v1) && Simd::mask(v2);
      }

      //! @} Overloadable and default functions
      //! @} Group SIMDAbstract
    } // namespace Overloads
  } // namespace Simd
} // namespace Dune

#endif // DUNE_COMMON_SIMD_DEFAULTS_HH