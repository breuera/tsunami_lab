#include "fwave.h"
#include <cmath>

void tsunami_lab::solvers::fwave::eigenwerte( t_real   i_hL,
                                t_real   i_hR,
                                t_real   i_uL,
                                t_real   i_uR,
                                t_real & o_waveSpeedL,
                                t_real & o_waveSpeedR ){

  t_real l_hSqrtL = std::sqrt( i_hL );
  t_real l_hSqrtR = std::sqrt( i_hR );

  // compute Roe averages
  t_real l_hRoe = 0.5f * ( i_hL + i_hR );
  t_real l_uRoe = l_hSqrtL * i_uL + l_hSqrtR * i_uR;
  l_uRoe /= l_hSqrtL + l_hSqrtR;

  // compute wave speeds
  t_real l_ghSqrtRoe = m_gSqrt * std::sqrt( l_hRoe );
  o_waveSpeedL = l_uRoe - l_ghSqrtRoe;
  o_waveSpeedR = l_uRoe + l_ghSqrtRoe;
}

void tsunami_lab::solvers::fwave::flux( t_real i_hL,
                                        t_real i_hR,
                                        t_real i_huL,
                                        t_real i_huR,
                                        t_real* & o_fdelta){
    
    t_real fql[2] = {i_huL, (pow(i_huL, 2) + 0.5 * (g * pow(i_hL, 2)))};
    t_real fqr[2] = {i_huR, (pow(i_huR, 2) + 0.5 * (g * pow(i_hR, 2)))};

    if (o_fdelta == nullptr) {
        o_fdelta = new t_real[2];
    }
    for (int i = 0; i < 2; i++) {
        o_fdelta[i] = fql[i] - fqr[i];
    }
}


void tsunami_lab::solvers::fwave::inverseMatrix(t_real i_eigen1,
                                                t_real i_eigen2,
                                                t_real o_inverse[4]){

    t_real det = i_eigen2 - i_eigen1;
    o_inverse[0] = i_eigen2 / det;
    o_inverse[1] = -1 / det;
    o_inverse[2] = -i_eigen1 / det;
    o_inverse[3] = 1 / det;
    
}

void tsunami_lab::solvers::fwave::netUpdates( t_real i_eigen1,
                                              t_real i_eigen2,
                                              t_real o_inverse[4]){
    
    t_real output[4]; 
    inverseMatrix(i_eigen1,i_eigen2,output);
    
}