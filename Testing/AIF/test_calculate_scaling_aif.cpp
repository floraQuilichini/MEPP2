#include "FEVV/DataStructures/AIF/AIFMesh.hpp"
#include "FEVV/Wrappings/Graph_traits_aif.h"
#include "FEVV/Wrappings/Geometry_traits_aif.h"

#include "FEVV/Wrappings/properties_aif.h"

using AIFKernel = FEVV::AIF_mesh_kernel_generator;
using MeshT = FEVV::DataStructures::AIF::AIFMesh;

//---------------- specific code above --------------------

//---------------- generic code below ---------------------

//#include "Testing/Utils/utils_retrieve_halfedge.h"
//#include "Testing/Utils/utils_are_meshes_identical.h"
#include "FEVV/Filters/Generic/scaling.hpp"

#include "FEVV/Filters/Generic/generic_reader.hpp"
// include "FEVV/Filters/Generic/generic_writer.hpp"

//---------------- generic code above ---------------------

//---------------- other code below -----------------------
#include <fstream>
#include <iostream>

void
test_calculate_scaling_aif(const std::string &input_file_path)
{
  typedef FEVV::Geometry_traits< MeshT > Geometry;
  typedef Geometry::Scalar Scalar;

  // read mesh from file
  MeshT m;
  FEVV::PMapsContainer pmaps_bag;
  FEVV::Filters::read_mesh(input_file_path, m, pmaps_bag);

  try
  {
    auto pos_pm = get(boost::vertex_point, m);
    FEVV::Filters::calculate_scaling(
        m, pos_pm, Scalar(2.0), Scalar(3.0), Scalar(4.0));
  }
  catch(...)
  {
    std::cout << "processing failed";
    return;
  }
  std::cout << "Done." << std::endl;
}

//------------------------------------------------------------------------------

int
main(int narg, char **argv)
{
  if(narg < 2)
  {
    std::cout << "Usage: " << argv[0]
              << " filename; filename being an off file." << std::endl;
    exit(EXIT_FAILURE);
  }

  test_calculate_scaling_aif(argv[1]);
  return 0;
}
