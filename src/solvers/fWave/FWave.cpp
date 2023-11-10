/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * F-Wave solver for the shallow water equations.
 */
#include "FWave.h"
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
    t_real l_hRoe = t_real(0.5) * (i_hL + i_hR);
    t_real l_uRoe = l_hSqrtL * i_uL + l_hSqrtR * i_uR;
    l_uRoe /= l_hSqrtL + l_hSqrtR;

    // compute wave speeds
    t_real l_ghSqrtRoe = m_gSqrt * std::sqrt(l_hRoe);
    o_waveSpeedL = l_uRoe - l_ghSqrtRoe;
    o_waveSpeedR = l_uRoe + l_ghSqrtRoe;
}

void tsunami_lab::solvers::FWave::flux(t_real i_h,
                                       t_real i_hu,
                                       t_real &o_flux0,
                                       t_real &o_flux1)
{
    // f(q) = [hu, h*u^2 + 1/2*g*h^2]
    o_flux0 = i_hu;
    o_flux1 = i_hu * i_hu / i_h + t_real(0.5) * m_g * i_h * i_h;
}

void tsunami_lab::solvers::FWave::deltaXPsi(t_real i_bL,
                                            t_real i_bR,
                                            t_real i_hL,
                                            t_real i_hR,
                                            t_real &o_deltaXPsi)
{
    // compute deltaXPsi
    o_deltaXPsi = -m_g * (i_bR - i_bL) * (i_hL + i_hR) / 2;
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
                                                t_real &o_strengthR)
{
    // compute inverse of right eigenvector-matrix
    t_real l_detInv = 1 / (i_waveSpeedR - i_waveSpeedL);

    t_real l_rInv[2][2] = {0};
    l_rInv[0][0] = l_detInv * i_waveSpeedR;
    l_rInv[0][1] = -l_detInv;
    l_rInv[1][0] = -l_detInv * i_waveSpeedL;
    l_rInv[1][1] = l_detInv;

    // calculating the fluxes
    t_real l_flux0L = 0;
    t_real l_flux1L = 0;
    t_real l_flux0R = 0;
    t_real l_flux1R = 0;
    t_real l_deltaXPsi = 0;

    flux(i_hL, i_huL, l_flux0L, l_flux1L);
    flux(i_hR, i_huR, l_flux0R, l_flux1R);
    deltaXPsi(i_bL, i_bR, i_hL, i_hR, l_deltaXPsi);

    // compute jump in fluxes
    t_real l_flux0Jump = l_flux0R - l_flux0L;
    t_real l_flux1Jump = l_flux1R - l_flux1L - l_deltaXPsi;

    // compute wave strengths
    o_strengthL = l_rInv[0][0] * l_flux0Jump;
    o_strengthL += l_rInv[0][1] * l_flux1Jump;

    o_strengthR = l_rInv[1][0] * l_flux0Jump;
    o_strengthR += l_rInv[1][1] * l_flux1Jump;
}

void tsunami_lab::solvers::FWave::netUpdates(t_real i_hL,
                                             t_real i_hR,
                                             t_real i_huL,
                                             t_real i_huR,
                                             t_real i_bL,
                                             t_real i_bR,
                                             t_real o_netUpdateL[2],
                                             t_real o_netUpdateR[2])
{
    bool l_updateL = true;
    bool l_updateR = true;
    // if both dry do nothing
    if (i_hL <= 0 && i_hR <= 0)
    {
        o_netUpdateL[0] = 0;
        o_netUpdateL[1] = 0;
        o_netUpdateR[0] = 0;
        o_netUpdateR[1] = 0;
        return;
    } // if only left side is dry, apply reflecting boundary condition
    else if (i_hL <= 0)
    {
        i_hL = i_hR;
        i_huL = -i_huR;
        i_bL = i_bR;
        l_updateL = false;
    } // if only right side is dry, apply reflecting boundary condition
    else if (i_hR <= 0)
    {
        i_hR = i_hL;
        i_huR = -i_huL;
        i_bR = i_bL;
        l_updateR = false;
    }

    // compute particle velocities
    t_real l_uL = i_huL / i_hL;
    t_real l_uR = i_huR / i_hR;

    // compute wave speeds
    t_real l_sL = 0;
    t_real l_sR = 0;

    waveSpeeds(i_hL,
               i_hR,
               l_uL,
               l_uR,
               l_sL,
               l_sR);

    // compute wave strengths
    t_real l_aL = 0;
    t_real l_aR = 0;

    waveStrengths(i_hL,
                  i_hR,
                  i_huL,
                  i_huR,
                  i_bL,
                  i_bR,
                  l_sL,
                  l_sR,
                  l_aL,
                  l_aR);

    // compute waves
    t_real l_waveL[2] = {0};
    t_real l_waveR[2] = {0};

    l_waveL[0] = l_aL;
    l_waveL[1] = l_aL * l_sL;

    l_waveR[0] = l_aR;
    l_waveR[1] = l_aR * l_sR;

    // set net-updates depending on wave speeds
    for (unsigned short l_qt = 0; l_qt < 2; l_qt++)
    {
        // init
        o_netUpdateL[l_qt] = 0;
        o_netUpdateR[l_qt] = 0;

        // 1st wave
        if (l_sL < 0 && l_updateL)
        {
            o_netUpdateL[l_qt] += l_waveL[l_qt];
        }
        else if (l_sL >= 0 && l_updateR)
        {
            o_netUpdateR[l_qt] += l_waveL[l_qt];
        }

        // 2nd wave
        if (l_sR > 0 && l_updateR)
        {
            o_netUpdateR[l_qt] += l_waveR[l_qt];
        }
        else if (l_sR >= 0 && l_updateL)
        {
            o_netUpdateL[l_qt] += l_waveR[l_qt];
        }
    }
}
