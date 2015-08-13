#ifndef STL2_DETAIL_RANGE_PRIMITIVES_HPP
#define STL2_DETAIL_RANGE_PRIMITIVES_HPP

#include <stl2/detail/fwd.hpp>
#include <stl2/detail/iterator/operations.hpp>
#include <stl2/detail/range/access.hpp>
#include <stl2/detail/range/concepts.hpp>

///////////////////////////////////////////////////////////////////////////
// Range primitives [range.primitives]
//
namespace stl2 { inline namespace v1 {

// distance
Range{R}
DifferenceType<R> distance(R&& r) {
  return stl2::distance(begin(r), end(r));
}

SizedRange{R}
DifferenceType<R> distance(R&& r) {
  return size(r);
}

}} // namespace stl2::v1

#endif
