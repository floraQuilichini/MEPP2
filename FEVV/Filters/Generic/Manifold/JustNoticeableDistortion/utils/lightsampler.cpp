#include "lightsampler.h"

void
LightSampler::sample(MatrixX3d &samples,
                     int n,
                     double phi_min,
                     double phi_max,
                     Method method,
                     bool use_random) const
{
  switch(method)
  {
  case NAIVE:
  default:
    sample_naive(samples, n, phi_min, phi_max, use_random);
    break;
  }
}

void
LightSampler::sample_to_global(MatrixX3d &samples,
                               int n,
                               const Vector3d &up,
                               double phi_min,
                               double phi_max,
                               bool use_random,
                               Method method) const
{
  MatrixX3d local;
  sample(local, n, phi_min, phi_max, method, use_random);
  to_global(local, samples, up);
}

void
LightSampler::to_global(const MatrixX3d &local,
                        MatrixX3d &global,
                        const Vector3d &up) const
{
  Vector3d oUp(Vector3d::UnitZ());

  double c = oUp.dot(up);
  if(c == 1.) // nothing to do
    global = local;
  else if(c == -1.) // opposite direction
    global = -local;
  else
  {
    Vector3d v = oUp.cross(up);
    Matrix3d vx;
    vx << 0, -v(2), v(1), v(2), 0, -v(0), -v(1), v(0), 0;
    vx = -vx;

    // compute rotation matrix
    Matrix3d R = Matrix3d::Identity() + vx + vx * vx / (1 + c);

    global = local * R;
  }
}

void
LightSampler::sample_naive(MatrixX3d &samples,
                           int n,
                           double phi_min,
                           double phi_max,
                           bool use_random) const
{
  samples.resize(n, 3);
  samples.setZero();

  std::random_device rd;
  std::mt19937 gen = std::mt19937(rd());

  double pi_2 = 2.0 * M_PI;
  double a = phi_min < phi_max ? phi_min : phi_max;
  double b = phi_min < phi_max ? phi_max : phi_min;
  std::uniform_real_distribution< double > dis1(0.0, pi_2);
  std::uniform_real_distribution< double > dis2(a, b);

  double step1 = pi_2 / (double)n;
  double step2 = 4.0 * (b - a) / (double)n;
  for(int i = 0; i < n; ++i)
  {
    double theta;
    double phi;
    if(use_random)
    {
      theta = dis1(gen);
      phi = dis2(gen);
    }
    else
    {
      theta = i * step1;
      phi = a + i * step2;
      while(phi > b)
        phi -= (b - a);
    }

    samples.row(i) << cos(theta) * sin(phi), sin(theta) * sin(phi), cos(phi);
  }
}
