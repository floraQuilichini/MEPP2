#ifndef TRIANGLE_RAD_ANGLE_HXX
#define TRIANGLE_RAD_ANGLE_HXX

#include "FEVV/Wrappings/Geometry_traits.h"
#include "FEVV/Operators/Geometry/AngleOperations.hpp"
#include "FEVV/Tools/Math/MatrixOperations.hpp" // MACH_EPS_DOUBLE

namespace FEVV {
namespace Operators {
namespace Geometry {
/**
 * \brief   Compute the angle of a triangle (given by 3 points).
 *
 * \tparam GeometryTraits The geometric kernel.
 * \param a The first point.
 * \param b The second point.
 * \param c The third point.
 * \param gt The geometry trait object.
 * \return The triangle angle in rad (Scalar).
 */
template< typename GeometryTraits >
inline typename GeometryTraits::Scalar
triangle_rad_angle(const typename GeometryTraits::Point &a,
                   const typename GeometryTraits::Point
                       &b, // the central point on which we compute the angle
                   const typename GeometryTraits::Point &c,
                   const GeometryTraits &gt)
{
  typedef typename GeometryTraits::Vector Vector;
  typedef typename GeometryTraits::Scalar Scalar;
  Vector ba(a[0] - b[0], a[1] - b[1], a[2] - b[2]),
      bc(c[0] - b[0], c[1] - b[1], c[2] - b[2]);
  Scalar lba = gt.length(ba), lbc = gt.length(bc);

  if(lba > MACH_EPS_DOUBLE)
    ba = ba / lba;
  else
    ba = gt.NULL_VECTOR;
  if(lbc > MACH_EPS_DOUBLE)
    bc = bc / lbc;
  else
    bc = gt.NULL_VECTOR;

  Scalar cosabc = gt.dot_product(ba, bc);

  return FEVV::Operators::Geometry::acos(cosabc);
}

} // namespace Geometry
} // namespace Operators
} // namespace FEVV

#endif // TRIANGLE_RAD_ANGLE_HXX
