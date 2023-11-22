/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * F Wave solver for the one-dimensional shallow water equations.
 **/

#include "FWave.h"

#include <cmath>
#include <iostream>

void tsunami_lab::solvers::FWave::heightAvg(t_real i_hL,
                                            t_real i_hR,
                                            t_real &o_height) {
    o_height = tsunami_lab::t_real(0.5) * (i_hL + i_hR);
}

void tsunami_lab::solvers::FWave::particleVelocityAvg(t_real i_hL,
                                                      t_real i_hR,
                                                      t_real i_uL,
                                                      t_real i_uR,
                                                      t_real &o_velocity) {
    t_real t_sqirt_hL = sqrt(i_hL);
    t_real t_sqirt_hR = sqrt(i_hR);
    o_velocity = i_uL * t_sqirt_hL + i_uR * t_sqirt_hR;
    o_velocity = o_velocity / (t_sqirt_hL + t_sqirt_hR);
}

void tsunami_lab::solvers::FWave::waveSpeeds(t_real i_hL,
                                             t_real i_hR,
                                             t_real i_uL,
                                             t_real i_uR,
                                             t_real &o_waveSpeedL,
                                             t_real &o_waveSpeedR) {
    // calculate Roe averages
    t_real l_height_avg = 0;
    t_real l_partical_vel_avg = 0;

    tsunami_lab::solvers::FWave::heightAvg(i_hL, i_hR, l_height_avg);
    tsunami_lab::solvers::FWave::particleVelocityAvg(i_hL, i_hR, i_uL, i_uR, l_partical_vel_avg);

    // calculate speeds
    o_waveSpeedL = l_partical_vel_avg - tsunami_lab::solvers::FWave::c_sqrt_g * sqrt(l_height_avg);
    o_waveSpeedR = l_partical_vel_avg + tsunami_lab::solvers::FWave::c_sqrt_g * sqrt(l_height_avg);
}

void tsunami_lab::solvers::FWave::flux(t_real i_h,
                                       t_real i_hu,
                                       t_real o_flux[2]) {
    o_flux[0] = i_hu;
    t_real l_u = i_hu / i_h;
    o_flux[1] = i_h * pow(l_u, 2) + tsunami_lab::t_real(0.5) * tsunami_lab::solvers::FWave::c_g * pow(i_h, 2);
}

void tsunami_lab::solvers::FWave::waveStrengths(t_real i_hL,
                                                t_real i_hR,
                                                t_real i_huL,
                                                t_real i_huR,
                                                t_real i_bL,
                                                t_real i_bR,
                                                t_real i_waveSpeedL,
                                                t_real i_waveSpeedR,
                                                t_real &o_strengthL,
                                                t_real &o_strengthR) {
    // calculate fluxes
    t_real l_fluxL[2] = {0};
    t_real l_fluxR[2] = {0};

    tsunami_lab::solvers::FWave::flux(i_hL, i_huL, l_fluxL);
    tsunami_lab::solvers::FWave::flux(i_hR, i_huR, l_fluxR);

    // calculate the delta of the flux functions
    t_real l_delta_flux[2] = {0};
    l_delta_flux[0] = l_fluxR[0] - l_fluxL[0];
    l_delta_flux[1] = l_fluxR[1] - l_fluxL[1];

    t_real l_delta_x_psi[2];
    l_delta_x_psi[0] = 0;
    l_delta_x_psi[1] = (-tsunami_lab::solvers::FWave::c_g) * (i_bR - i_bL) * ((i_hL + i_hR) / 2);

    t_real l_decomposition_flux[2];
    l_decomposition_flux[0] = l_delta_flux[0] - l_delta_x_psi[0];
    l_decomposition_flux[1] = l_delta_flux[1] - l_delta_x_psi[1];

    // calculate reversed determinant
    t_real l_rev_det = 1 / (i_waveSpeedR - i_waveSpeedL);

    // calculate the inverse of the matrix R
    t_real l_R_inv[2][2] = {0};
    l_R_inv[0][0] = l_rev_det * i_waveSpeedR;
    l_R_inv[0][1] = -l_rev_det;
    l_R_inv[1][0] = -l_rev_det * i_waveSpeedL;
    l_R_inv[1][1] = l_rev_det;

    // calculate wave strengths
    o_strengthL = l_R_inv[0][0] * l_decomposition_flux[0];
    o_strengthL += l_R_inv[0][1] * l_decomposition_flux[1];
    o_strengthR = l_R_inv[1][0] * l_decomposition_flux[0];
    o_strengthR += l_R_inv[1][1] * l_decomposition_flux[1];
}

void tsunami_lab::solvers::FWave::netUpdates(t_real i_hL,
                                             t_real i_hR,
                                             t_real i_huL,
                                             t_real i_huR,
                                             t_real i_bL,
                                             t_real i_bR,
                                             t_real o_netUpdateL[2],
                                             t_real o_netUpdateR[2]) {
    bool l_isLeftDry = (i_hL <= 0);
    bool l_isRightDry = (i_hR <= 0);

    // set netUpdates to zero if both cells are dry
    if (l_isLeftDry && l_isRightDry) {
        for (int l_idx = 0; l_idx < 2; l_idx++) {
            o_netUpdateL[l_idx] = 0;
            o_netUpdateR[l_idx] = 0;
        }

        return;
    }

    // if left cell is dry set left to reflecting
    if (l_isLeftDry) {
        i_hL = i_hR;
        i_huL = -i_huR;
        i_bL = i_bR;
    }

    // if right cell is dry set right to reflecting
    if (l_isRightDry) {
        i_hR = i_hL;
        i_huR = -i_huL;
        i_bR = i_bL;
    }

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

    waveStrengths(i_hL, i_hR, i_huL, i_huR, i_bL, i_bR, l_waveSpeedL, l_waveSpeedR, l_waveStrengthL, l_waveStrengthR);

    // calculate waves
    t_real l_waveL[2] = {0};
    t_real l_waveR[2] = {0};

    l_waveL[0] = l_waveStrengthL;
    l_waveL[1] = l_waveStrengthL * l_waveSpeedL;

    l_waveR[0] = l_waveStrengthR;
    l_waveR[1] = l_waveStrengthR * l_waveSpeedR;

    // set netUpdates
    for (int i = 0; i < 2; i++) {
        o_netUpdateL[i] = 0;
        o_netUpdateR[i] = 0;

        // left wave
        if (l_waveSpeedL < 0 && !l_isLeftDry) {
            // left-going wave
            o_netUpdateL[i] += l_waveL[i];
        } else if (l_waveSpeedL >= 0 && !l_isRightDry) {
            // right-going wave
            o_netUpdateR[i] += l_waveL[i];
        }

        // right wave
        if (l_waveSpeedR > 0 && !l_isRightDry) {
            // right-going wave
            o_netUpdateR[i] += l_waveR[i];
        } else if (l_waveSpeedR <= 0 && !l_isLeftDry) {
            // left-going wave
            o_netUpdateL[i] += l_waveR[i];
        }
    }
}
