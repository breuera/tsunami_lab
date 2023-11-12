/**
 * @author Maurice Herold (maurice.herold AT uni-jena.de)
 * @author Mher Mnatsakanyan (mher. AT uni-jena.de)
 *
 *
 * @section DESCRIPTION
 * F-Wave solver for one dimensional shallow water equations.
 */
#include "F_wave.h"

#include "cmath"
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

    // compute FWave averages
    t_real l_hRoe = 0.5f * (i_hL + i_hR);
    t_real l_uRoe = l_hSqrtL * i_uL + l_hSqrtR * i_uR;
    l_uRoe /= l_hSqrtL + l_hSqrtR;

    // compute wave speeds
    t_real l_ghSqrtRoe = m_gSqrt * std::sqrt(l_hRoe);
    o_waveSpeedL = l_uRoe - l_ghSqrtRoe;
    o_waveSpeedR = l_uRoe + l_ghSqrtRoe;
}

void tsunami_lab::solvers::FWave::flux(t_real i_h,
                                       t_real i_hu,
                                       t_real *o_flux)
{
    o_flux[0] = i_hu;
    o_flux[1] = i_hu * i_hu / i_h + m_g * (0.5f * i_h * i_h);
}

void tsunami_lab::solvers::FWave::deltaXPsi(t_real i_hL,
                                            t_real i_hR,
                                            t_real i_bL,
                                            t_real i_bR,
                                            t_real *o_deltaXPsi)
{
    o_deltaXPsi[0] = 0;
    o_deltaXPsi[1] = -1 * m_g * (i_bR - i_bL) * (i_hL + i_hR) * 0.5;
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

    t_real l_fluxL[2] = {0};
    t_real l_fluxR[2] = {0};

    flux(i_hL, i_huL, l_fluxL);
    flux(i_hR, i_huR, l_fluxR);

    t_real l_deltaXPsi[2] = {0};

    deltaXPsi(i_hL, i_hR, i_bL, i_bR, l_deltaXPsi);

    t_real l_fluxJump[2];

    l_fluxJump[0] = l_fluxR[0] - l_fluxL[0] - l_deltaXPsi[0];
    l_fluxJump[1] = l_fluxR[1] - l_fluxL[1] - l_deltaXPsi[1];

    // compute wave strengths
    o_strengthL = l_rInv[0][0] * l_fluxJump[0];
    o_strengthL += l_rInv[0][1] * l_fluxJump[1];

    o_strengthR = l_rInv[1][0] * l_fluxJump[0];
    o_strengthR += l_rInv[1][1] * l_fluxJump[1];
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
    // both sides are dry -> exit 0
    if (i_hL <= 0 && i_hR <= 0)
    {
        o_netUpdateL[0] = 0;
        o_netUpdateL[1] = 0;
        o_netUpdateR[0] = 0;
        o_netUpdateR[1] = 0;
        return;
    }

    // if dry, then no need to update
    bool do_update_left = true;
    bool do_update_right = true;

    // left side dry -> reflect to right
    if (i_hL <= 0)
    {
        i_hL = i_hR;
        i_huL = -i_huR;
        i_bL = i_bR;
        do_update_left = false;
    }
    // right side dry -> reflect to left
    else if (i_hR <= 0)
    {
        i_hR = i_hL;
        i_huR = -i_huL;
        i_bR = i_bL;
        do_update_right = false;
    }

    // compute particle velocities
    t_real l_uL = i_huL / i_hL;
    t_real l_uR = i_huR / i_hR;

    // compute wave speeds
    t_real l_sL = 0;
    t_real l_sR = 0;

    waveSpeeds(i_hL, i_hR, l_uL, l_uR, l_sL, l_sR);

    // compute wave strengths
    t_real l_aL = 0;
    t_real l_aR = 0;

    waveStrengths(i_hL, i_hR, i_huL, i_huR, i_bL, i_bR, l_sL, l_sR, l_aL, l_aR);

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
        if (l_sL < 0 && do_update_left)
        {
            o_netUpdateL[l_qt] += l_waveL[l_qt];
        }
        else if (l_sL >= 0 && do_update_right)
        {
            o_netUpdateR[l_qt] += l_waveL[l_qt];
        }

        // 2nd wave
        if (l_sR > 0 && do_update_right)
        {
            o_netUpdateR[l_qt] += l_waveR[l_qt];
        }
        else if (l_sR >= 0 && do_update_left)
        {
            o_netUpdateL[l_qt] += l_waveR[l_qt];
        }
    }
}