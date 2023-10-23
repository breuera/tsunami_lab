#include "F_wave.h"
#include <cmath>

void tsunami_lab::solvers::FWave::height_avg( t_real i_hL,
                                              t_real i_hR,
                                              t_real & o_height) {
    o_height = 0.5f * (i_hL + i_hR);                                               
}

void tsunami_lab::solvers::FWave::particle_vel_avg( t_real i_hL,
                                                    t_real i_hR,
                                                    t_real i_uL,
                                                    t_real i_uR,
                                                    t_real & o_velocity) {
    t_real t_sqirt_hL = sqrt(i_hL);
    t_real t_sqirt_hR = sqrt(i_hR);
    o_velocity = i_uL * t_sqirt_hL + i_uR * t_sqirt_hR;
    o_velocity = o_velocity / (t_sqirt_hL + t_sqirt_hR);
}

void tsunami_lab::solvers::FWave::waveSpeed( t_real   i_hL,
                                             t_real   i_hR,
                                             t_real   i_uL,
                                             t_real   i_uR,
                                             t_real & o_waveSpeedL,
                                             t_real & o_waveSpeedR) {
    // calculate Roe averages
    t_real t_height_avg = 0;
    t_real t_partical_vel_avg = 0;

    height_avg(i_hL, i_hR, t_height_avg);
    particle_vel_avg(i_hL, i_hR, i_uL, i_uR, t_partical_vel_avg);

    
}

