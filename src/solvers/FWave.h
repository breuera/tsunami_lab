/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * F Wave solver for the one-dimensional shallow water equations.
 **/

#ifndef TSUNAMI_LAB_SOLVERS_F_WAFE
#define TSUNAMI_LAB_SOLVERS_F_WAFE

#include "../constants.h"

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
	//! gravity constant
	static t_real constexpr c_g = 9.80665;

	//! square root of gravity
	static t_real constexpr c_sqrt_g = 3.131557121;

	/**
	 * Computes the average wave height.
	 *
	 * @param i_hL height of the left side.
	 * @param i_hR height of the right side.
	 * @param o_hight will be set to the average speed.
	 **/

	static void heightAvg(t_real i_hL,
						  t_real i_hR,
						  t_real &o_height);

	/**
	 * Computes the average particle_Velocity
	 *
	 * @param i_hL height of the left side.
	 * @param i_hR height of the right side.
	 * @param i_huL momentum of the left side.
	 * @param i_huR momentum of the right side.
	 * @param o_velocity will be set to the average velocity.
	 **/

	static void particleVelocityAvg(t_real i_hL,
									t_real i_hR,
									t_real i_uL,
									t_real i_uR,
									t_real &o_velocity);
	/**
	 * Computes the wave speeds.
	 *
	 * @param i_hL height of the left side.
	 * @param i_hR height of the right side.
	 * @param i_huL momentum of the left side.
	 * @param i_huR momentum of the right side.
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
	 * Computes the flux function for one cell.
	 *
	 * @param i_h height of the cell
	 * @param i_hu momentum of the cell
	 * @param o_flux will be set to the flux function value
	 **/
	static void flux(t_real i_h,
					 t_real i_hu,
					 t_real o_flux[2]);

	/**
	 * Computes the wave strengths
	 *
	 * @param i_hL height of the left side.
	 * @param i_hR height of the right side.
	 * @param i_huL momentum of the left side.
	 * @param i_huR momentum of the right side.
	 * @param i_bL bathymetry of the left side.
	 * @param i_bR bathymetry of the right side.
	 * @param i_waveSpeedL wave speed of the left side.
	 * @param i_waveSpeedR wave speed of the right side.
	 * @param o_strengthL will be set to the strength of the wave propagation to the left.
	 * @param o_strengthR will be set to the strength of the wave propagation to the right.
	 **/

	static void waveStrengths( t_real i_hL,
							   t_real i_hR,
							   t_real i_huL,
							   t_real i_huR,
							   t_real i_bL,
							   t_real i_bR,
							   t_real i_waveSpeedL,
							   t_real i_waveSpeedR,
							   t_real &o_strengthL,
							   t_real &o_strengthR);

public:
	/**
	 * Computes the net-updates.
	 *
	 * @param i_hL height of the left side.
	 * @param i_hR height of the right side.
	 * @param i_huL momentum of the left side.
	 * @param i_huR momentum of the right side.
	 * @param i_bL bathymetry of the left side.
	 * @param i_bR bathymetry of the right side.
	 * @param o_netUpdateL will be set to the net-updates for the left side; 0: hight 1: momentum.
	 * @param o_netUpdateR will be set to the net-updates for the right side; 0: hight, 1: momentum.
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
