#include <fstream>
#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>

#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>

#include "FEVV/Wrappings/Geometry_traits_cgal_polyhedron_3.h"

#include "FEVV/Filters/Generic/calculate_face_normals.hpp"
#include "FEVV/Filters/Generic/scaling.hpp"
#include "FEVV/Operators/Generic/Manifold/collapse_edge.hpp"
#include "FEVV/Filters/Generic/translation.hpp"
#include "FEVV/Filters/translation_with_object.h"
#include "FEVV/Filters/Generic/print_points.hpp"
#include "FEVV/Filters/Generic/print_face_normals.hpp"

using namespace FEVV;
using namespace FEVV::Filters;

//------------------------------------------------------------------------------
void
test_polyhedron(char *filename)
{
  typedef CGAL::Cartesian< double > Kernel;
  typedef Kernel::Vector_3 Vector;
  typedef CGAL::Polyhedron_3< Kernel, CGAL::Polyhedron_items_with_id_3 >
      Polyhedron;
  typedef boost::property_map< Polyhedron, CGAL::face_index_t >::const_type
      Face_index_map;

  // 1) Load a mesh
  std::ifstream in(filename);
  Polyhedron p;
  try
  {
    in >> p;

    // initialize facet indices
    std::size_t i = 0;
    for(Polyhedron::Facet_iterator it = p.facets_begin(); it != p.facets_end();
        ++it, ++i)
    {
      it->id() = i;
    }
  }
  catch(const std::length_error &le)
  {
    std::cerr << "[Polyhedron] Exception caught while reading input file "
              << filename << ": " << le.what() << std::endl;
    BOOST_ASSERT_MSG(false,
                     "[Polyhedron] Exception caught while reading input file.");
  }

  // 2) Add face normal property
  // Ad hoc property_map to store normals. Face_index_map is used to
  // map face_descriptors to a contiguous range of indices. See
  // http://www.boost.org/libs/property_map/doc/vector_property_map.html
  // for details.
  boost::vector_property_map< Vector, Face_index_map > normals(
      get(CGAL::face_index, p));

  auto pos_pm = get(CGAL::vertex_point, p);

  // 3) Compute normals
  calculate_face_normals(p // Graph
                         ,
                         pos_pm // map from vertex_descriptor to point
                         ,
                         normals // map from face_descriptor to Vector_3
  );

  // 4) Draw normals
  print_face_normals(p, normals);

  // 5) Scale the mesh
  calculate_scaling(p, pos_pm, 2.0, 3.0, 4.0);

  // 6) Display the points
  print_points(p, pos_pm);

  // 7) Collapse some edges
  /*std::cout << "Start collapsing edges ..." << std::endl;
  collapse_some_edges(P);
  std::ofstream collapse_some_edges_os("collapse_some_edges.off");
  collapse_some_edges_os << P;*/

  // 8) Translate object
  // 8.1) First by using a global function
  translate(p, pos_pm, 10, 5, 3);

  // 8.2) Second by using an object
  TranslationFilter< Polyhedron, decltype(pos_pm) > tf(p, pos_pm);
  tf.translate(-10, -5, -3);

  // End of test
  std::cout << "Done." << std::endl;
}

//------------------------------------------------------------------------------
int
main(int narg, char **argv)
{
  if(narg < 2)
  {
    std::cout << "Usage: a.out filename; filename being an off file."
              << std::endl;
    exit(EXIT_FAILURE);
  }

  test_polyhedron(argv[1]);
  return 0;
}
