/**
 * @author Justus Dreßler (justus.dressler AT uni-jena.de)
 * @author Thorsten Kröhl (thorsten.kroehl AT uni-jena.de)
 * @author Julius Halank (julius.halank AT uni-jena.de)
 *
 * @section DESCRIPTION
 * F-Wave solver for one dimensional shallow water equations.
 */
#ifndef TSUNAMI_LAB_SOLVERS_FWAVE
#define TSUNAMI_LAB_SOLVERS_FWAVE

#include "../../constants.h"

namespace tsunami_lab
{
    namespace solvers
    {
        class FWave;
    }
}

class tsunami_lab::solvers::FWave
{
private:
    //! gravity
    static t_real constexpr m_g = 9.80665;
    //! square root of gravity
    static t_real constexpr m_gSqrt = 3.131557121;

    /**
     * Computes the wave speeds.
     *
     * @param i_hL height of the left side.
     * @param i_hR height of the right side.
     * @param i_uL particle velocity of the leftside.
     * @param i_uR particles velocity of the right side.
     * @param o_waveSpeedL will be set to the speed of the wave propagating to the left.
     * @param o_waveSpeedR will be set to the speed of the wave propagating to the right.
     **/
    static void waveSpeeds(t_real i_hL,
                           t_real i_hR,
                           t_real i_uL,
                           t_real i_uR,
                           t_real &o_waveSpeedL,
                           t_real &o_waveSpeedR);

    /**
     * Computes the wave strengths.
     *
     * @param i_hL height of the left side.
     * @param i_hR height of the right side.
     * @param i_huL momentum of the left side.
     * @param i_huR momentum of the right side.
     * @param i_bl bathymetry of the left side.
     * @param i_br bathymetry of the right side.
     * @param i_waveSpeedL speed of the wave propagating to the left.
     * @param i_waveSpeedR speed of the wave propagating to the right.
     * @param o_strengthL will be set to the strength of the wave propagating to the left.
     * @param o_strengthR will be set to the strength of the wave propagating to the right.
     **/
    static void waveStrengths(t_real i_hL,
                              t_real i_hR,
                              t_real i_huL,
                              t_real i_huR,
                              t_real i_bL,
                              t_real i_bR,
                              t_real i_waveSpeedL,
                              t_real i_waveSpeedR,
                              t_real &o_strengthL,
                              t_real &o_strengthR);

    /**
     * Computes the Flux .
     *
     * @param i_h height
     * @param i_hu momentum
     * @param o_flux0 fluxfunction[0]
     * @param o_flux1 fluxfunction[1]
     **/
    static void flux(t_real i_h,
                     t_real i_hu,
                     t_real &o_flux0,
                     t_real &o_flux1);

    /**
     * @brief calculates the difference in the source term
     *
     * @param i_bL left bathymetry
     * @param i_bR right bathymetry
     * @param i_hL left height
     * @param i_hR right height
     * @param o_deltaXPsi difference in the source term
     */
    static void deltaXPsi(t_real i_bL,
                          t_real i_bR,
                          t_real i_hL,
                          t_real i_hR,
                          t_real &o_deltaXPsi);

public:
    /**
     * Computes the net-updates.
     *
     * @param i_hL height of the left side.
     * @param i_hR height of the right side.
     * @param i_huL momentum of the left side.
     * @param i_huR momentum of the right side.
     * @param i_bL left bathymetry
     * @param i_bR right bathymetry
     * @param o_netUpdateL will be set to the net-updates for the left side; 0: height, 1: momentum.
     * @param o_netUpdateR will be set to the net-updates for the right side; 0: height, 1: momentum.
     **/
    static void netUpdates(t_real i_hL,
                           t_real i_hR,
                           t_real i_huL,
                           t_real i_huR,
                           t_real i_bL,
                           t_real i_bR,
                           t_real o_netUpdateL[2],
                           t_real o_netUpdateR[2]);
};

#endif