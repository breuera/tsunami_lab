#include <F_wave.h>
#include <cmath>

void tsunami_lab::solvers::FWave::waveSpeeds(t_real i_hL,
                                             t_real i_hR,
                                             t_real i_uL,
                                             t_real i_uR,
                                             t_real &o_waveSpeedL,
                                             t_real &o_waveSpeedR)
{
  // pre-compute square-root ops
  t_real l_hSqrtL = std::sqrt(i_hL);
  t_real l_hSqrtR = std::sqrt(i_hR);

  // compute Roe averages
  t_real l_hRoe = 0.5f * (i_hL + i_hR);
  t_real l_uRoe = l_hSqrtL * i_uL + l_hSqrtR * i_uR;
  l_uRoe /= l_hSqrtL + l_hSqrtR;

  // compute wave speeds
  t_real l_ghSqrtRoe = m_gSqrt * std::sqrt(l_hRoe);
  o_waveSpeedL = l_uRoe - l_ghSqrtRoe;
  o_waveSpeedR = l_uRoe + l_ghSqrtRoe;
}

void tsunami_lab::solvers::FWave::waveStrengths(t_real i_hL,
                                                t_real i_hR,
                                                t_real i_huL,
                                                t_real i_huR,
                                                t_real i_waveSpeedL,
                                                t_real i_waveSpeedR,
                                                t_real &o_strengthL,
                                                t_real &o_strengthR)
{
}