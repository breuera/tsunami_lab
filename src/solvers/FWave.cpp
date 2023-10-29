/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * F Wave solver for the one-dimensional shallow water equations.
**/

#include "FWave.h"
#include <cmath>

void tsunami_lab::solvers::F_Wave::heightAvg( t_real   i_hL,
                                             t_real   i_hR,
                                             t_real & o_height) {
    o_height = 0.5f * (i_hL + i_hR);                                               
}

void tsunami_lab::solvers::F_Wave::particleVelocityAvg( t_real   i_hL,
                                                        t_real   i_hR,
                                                        t_real   i_uL,
                                                        t_real   i_uR,
                                                        t_real & o_velocity) {
    t_real t_sqirt_hL = sqrt(i_hL);
    t_real t_sqirt_hR = sqrt(i_hR);
    o_velocity = i_uL * t_sqirt_hL + i_uR * t_sqirt_hR;
    o_velocity = o_velocity / (t_sqirt_hL + t_sqirt_hR);
}

void tsunami_lab::solvers::F_Wave::waveSpeeds( t_real   i_hL,
                                               t_real   i_hR,
                                               t_real   i_uL,
                                               t_real   i_uR,
                                               t_real & o_waveSpeedL,
                                               t_real & o_waveSpeedR) {
    // calculate Roe averages
    t_real l_height_avg = 0;
    t_real l_partical_vel_avg = 0;

    tsunami_lab::solvers::F_Wave::heightAvg(i_hL, i_hR, l_height_avg);
    tsunami_lab::solvers::F_Wave::particleVelocityAvg(i_hL, i_hR, i_uL, i_uR, l_partical_vel_avg);

    // calculate speeds
    o_waveSpeedL = l_partical_vel_avg - tsunami_lab::solvers::F_Wave::c_sqrt_g * sqrt(l_height_avg);
    o_waveSpeedR = l_partical_vel_avg + tsunami_lab::solvers::F_Wave::c_sqrt_g * sqrt(l_height_avg);
}

void tsunami_lab::solvers::F_Wave::waveStrengths( t_real   i_hL,
								                  t_real   i_hR,
								                  t_real   i_huL,
								                  t_real   i_huR,
								                  t_real   i_waveSpeedL,
                               	                  t_real   i_waveSpeedR,
								                  t_real & o_strengthL,
								                  t_real & o_strengthR) {
    //calculate jumps
    t_real l_h_jump = i_hR - i_hL;
    t_real l_hu_jump = i_huR - i_huL;

    //calculate reversed determinant
    t_real l_rev_det = 1 / (i_waveSpeedR - i_waveSpeedL);

    //calculate wave strengths
    o_strengthL = l_rev_det * i_waveSpeedR * l_h_jump - l_rev_det * l_hu_jump;
    o_strengthR = l_rev_det * l_hu_jump - l_rev_det * i_waveSpeedL * l_h_jump;
}

void tsunami_lab::solvers::F_Wave::netUpdates( t_real i_hL,
								               t_real i_hR,
								               t_real i_huL,
								               t_real i_huR,
								               t_real o_netUpdateL[2],
								               t_real o_netUpdateR[2]) {
    // calculate particle velocity
    t_real l_uL = i_huL / i_hL;
    t_real l_uR = i_huR / i_hR;

    // calculate wavespeeds
    t_real l_waveSpeedL = 0;
    t_real l_waveSpeedR = 0;
    
    waveSpeeds(i_hL, i_hR, l_uL, l_uR, l_waveSpeedL, l_waveSpeedR);

    // calculate wave strengths
    t_real l_waveStrengthL = 0;
    t_real l_waveStrengthR = 0;

    waveStrengths(i_hL, i_hR, i_huL, i_huR, l_waveSpeedL, l_waveSpeedR, l_waveStrengthL, l_waveStrengthR);

    // calculate waves
    t_real l_waveL[2] = {0};
    t_real l_waveR[2] = {0};

    l_waveL[0] = l_waveStrengthL;
    l_waveL[1] = l_waveStrengthL * l_waveSpeedL;

    l_waveR[0] = l_waveStrengthR;
    l_waveR[1] = l_waveStrengthR * l_waveSpeedR;

    // set netUpdates  
    for(int i = 0; i < 2; i++) {
        o_netUpdateL[i] = 0;
        o_netUpdateR[i] = 0;

        // left wave
        if(l_waveSpeedL < 0) {
            //left-going wave
            o_netUpdateL[i] = l_waveL[i];
        } else {
            //right-going wave
            o_netUpdateR[i] = l_waveL[i];
        }

        // right wave
        if(l_waveSpeedR > 0){
            // right-going wave
            o_netUpdateR[i] = l_waveR[i];
        } else {
            // left-going wave
            o_netUpdateL[i] = l_waveR[i];
        }
    }
}
