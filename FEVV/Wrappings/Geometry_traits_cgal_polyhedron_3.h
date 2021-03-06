#ifndef GEOMETRY_TRAITS_CGAL_POLYHEDRON_3_H
#define GEOMETRY_TRAITS_CGAL_POLYHEDRON_3_H

#include <CGAL/Polyhedron_3.h>
#include "FEVV/Wrappings/Geometry_traits.h"
#include "FEVV/Wrappings/Geometry_traits_cartesian.h"
#include "FEVV/Wrappings/Geometry_traits_cgal_exact_predicates_inexact_constructions_kernel.h"
#include "FEVV/Wrappings/Geometry_traits_operators.h"

namespace FEVV {

/**
 * \ingroup Geometry_traits_group
 * \anchor  RetrieveKernel_specialization_cgal_Polyhedron
 * \brief   OpenMesh specialization. Refer to \ref RetrieveKernel for the
 *          documentation of the generic class.
 */
template< typename T1, // class PolyhedronTraits_3
          typename T2, // class PolyhedronItems_3 =
                       //   CGAL::Polyhedron_items_3,
          template< class A,
                    class B,
                    class C > class T3, // class T_HDS = HalfedgeDS_default
          typename T4 >                 // class Alloc = CGAL_ALLOCATOR(int)
struct RetrieveKernel< CGAL::Polyhedron_3< T1, T2, T3, T4 > >
{
  typedef typename CGAL::Polyhedron_3< T1, T2, T3, T4 >::Traits Kernel;
  /// Caveat emptor: in fact this kernel can be any model of the CGAL::Kernel
  /// model e.g. CGAL::Cartesian< > or CGAL::Simple_cartesian<FieldNumberType>.
  /// This specialization is thus not terminal and relies on another
  /// Geometric_traits specialization explictly defined somewhere else
  /// e.g. Geometry_traits< Mesh, CGAL::Cartesian< > >.
  /// Thus if you end up in this comment because you cannot instantiate
  /// a Geometric_traits for some CGAL::Polyhedron_3< T1,... > mesh, it
  /// might well be that you need to define a Geometry_traits ad-hoc
  /// specialisation for the T1 type of kernels...
};

} // namespace FEVV

#endif // GEOMETRY_TRAITS_CGAL_POLYHEDRON_3_H
