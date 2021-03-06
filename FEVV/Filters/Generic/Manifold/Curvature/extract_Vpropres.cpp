#include "extract_Vpropres.h"

#include <iostream>
#include <Eigen/Eigenvalues>
#include <cmath> // for std::abs()
#include <vector>


int
val_pro(const EigenMatrix &a, EigenvectorsType &u, EigenvalueType &ad)
{
  Eigen::EigenSolver< EigenMatrix > solver(a, true);
  // ELO-note:
  //  solver.eigenvalues() and solver.eigenvectors() return
  //  matrices of std::complex values ; here we keep only
  //  the real part of this values
  ad = solver.eigenvalues().real();
  u = solver.eigenvectors().real();

  // TODO-elo check if the values are 'good', return -1 if not

  return 0;
}


void
eig_srt(EigenvalueType &ad, EigenvectorsType &u)
{
  // sort eigenvalues indices by descending order of their absolute values
  std::vector< size_t > sorted_indices;
  sorted_indices.push_back(0);
  for(int i = 1; i < 3; i++)
  {
    // find the place where to insert current eigenvalue
    auto it = sorted_indices.begin();
    for(; it != sorted_indices.end(); ++it)
    {
      if(std::abs(ad(*it)) < std::abs(ad(i)))
        break;
    }

    // insert current eigenvalue index here
    sorted_indices.insert(it, i);
  }

  // sort eigenvalues and eigenvectors
  EigenvalueType sorted_eigen_val;
  EigenvectorsType sorted_eigen_vect;

  for(int i = 0; i < 3; i++)
  {
    sorted_eigen_val(i) = ad(sorted_indices[i]);
    sorted_eigen_vect.col(i) = u.col(sorted_indices[i]);
  }

  ad = sorted_eigen_val;
  u = sorted_eigen_vect;
}
