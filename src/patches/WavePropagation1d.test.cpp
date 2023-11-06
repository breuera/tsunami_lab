/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests for the one-dimensional wave propagation patch.
 **/
#include <catch2/catch.hpp>
#include "WavePropagation1d.h"

TEST_CASE("Test the 1d wave propagation roe solver.", "[WaveProp1dRoe]")
{
  /*
   * Test case:
   *
   *   Single dam break problem between cell 49 and 50.
   *     left | right
   *       10 | 8
   *        0 | 0
   *
   *   Elsewhere steady state.
   *
   * The net-updates at the respective edge are given as
   * (see derivation in Roe solver):
   *    left          | right
   *      9.394671362 | -9.394671362
   *    -88.25985     | -88.25985
   */

  // construct solver and setup a dambreak problem
  tsunami_lab::patches::WavePropagation1d m_waveProp(100, false);

  for (std::size_t l_ce = 0; l_ce < 50; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         10);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            0);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }
  for (std::size_t l_ce = 50; l_ce < 100; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         8);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            0);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }

  // set outflow boundary condition
  m_waveProp.setGhostOutflow();

  // perform a time step
  m_waveProp.timeStep(0.1);

  // steady state
  for (std::size_t l_ce = 0; l_ce < 49; l_ce++)
  {
    REQUIRE(m_waveProp.getHeight()[l_ce] == Approx(10));
    REQUIRE(m_waveProp.getMomentumX()[l_ce] == Approx(0));
  }

  // dam-break
  REQUIRE(m_waveProp.getHeight()[49] == Approx(10 - 0.1 * 9.394671362));
  REQUIRE(m_waveProp.getMomentumX()[49] == Approx(0 + 0.1 * 88.25985));

  REQUIRE(m_waveProp.getHeight()[50] == Approx(8 + 0.1 * 9.394671362));
  REQUIRE(m_waveProp.getMomentumX()[50] == Approx(0 + 0.1 * 88.25985));

  // steady state
  for (std::size_t l_ce = 51; l_ce < 100; l_ce++)
  {
    REQUIRE(m_waveProp.getHeight()[l_ce] == Approx(8));
    REQUIRE(m_waveProp.getMomentumX()[l_ce] == Approx(0));
  }
}

TEST_CASE("Test the 1d wave propagation FWave solver.", "[WaveProp1dFWave]")
{
  /*
   * Test case:
   *
   *   Single dam break problem between cell 49 and 50.
   *     left | right
   *       10 | 8
   *        0 | 0
   *
   *   Elsewhere steady state.
   *
   * The net-updates at the respective edge are given as
   * (see derivation in FWave solver):
   *    left          | right
   *      9.39468     | -9.39468
   *    -88.2599     | -88.2599
   */

  // construct solver and setup a dambreak problem
  tsunami_lab::patches::WavePropagation1d m_waveProp(100, true);

  for (std::size_t l_ce = 0; l_ce < 50; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         10);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            0);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }
  for (std::size_t l_ce = 50; l_ce < 100; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         8);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            0);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }

  // set outflow boundary condition
  m_waveProp.setGhostOutflow();

  // perform a time step
  m_waveProp.timeStep(0.1);

  // steady state
  for (std::size_t l_ce = 0; l_ce < 49; l_ce++)
  {
    REQUIRE(m_waveProp.getHeight()[l_ce] == Approx(10));
    REQUIRE(m_waveProp.getMomentumX()[l_ce] == Approx(0));
  }

  // dam-break
  REQUIRE(m_waveProp.getHeight()[49] == Approx(10 - 0.1 * 9.39468));
  REQUIRE(m_waveProp.getMomentumX()[49] == Approx(0 + 0.1 * 88.2599));

  REQUIRE(m_waveProp.getHeight()[50] == Approx(8 + 0.1 * 9.39468));
  REQUIRE(m_waveProp.getMomentumX()[50] == Approx(0 + 0.1 * 88.2599));

  // steady state
  for (std::size_t l_ce = 51; l_ce < 100; l_ce++)
  {
    REQUIRE(m_waveProp.getHeight()[l_ce] == Approx(8));
    REQUIRE(m_waveProp.getMomentumX()[l_ce] == Approx(0));
  }
}

TEST_CASE("Test the 1d wave propagation FWave solver shock-shock.", "[WaveProp1dFWaveShockShock]")
{
  /**
   * @brief test steady state from middle_states.csv in the Shock-Shock Problem
   * (Riemann Solutions obtained by Alexander Breuer)
   *
   * h_l = 9894.065328676988
   * h_r = 9894.065328676988
   * hu_l = 763.616897222239
   * hu_r = -763.616897222239
   * h* = 9896.516538751875
   */

  // construct solver and setup a shock-shock problem
  tsunami_lab::patches::WavePropagation1d m_waveProp(100, true);

  for (std::size_t l_ce = 0; l_ce < 50; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         9894.065328676988);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            763.616897222239);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }
  for (std::size_t l_ce = 50; l_ce < 100; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         9894.065328676988);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            -763.616897222239);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }

  // set outflow boundary condition
  m_waveProp.setGhostOutflow();

  // perform a time step
  for (int i = 0; i < 30; i++)
  {
    m_waveProp.timeStep(0.001);
  }

  // test for h*
  REQUIRE(m_waveProp.getHeight()[49] == Approx(9896.516538751875));
  REQUIRE(m_waveProp.getHeight()[50] == Approx(9896.516538751875));
}

TEST_CASE("Test the 1d wave propagation FWave solver rare-rare.", "[WaveProp1dFWaveRareRare]")
{
  /**
   * @brief test steady state from middle_states.csv in the Shock-Shock Problem
   * (Riemann Solutions obtained by Alexander Breuer)
   *
   * h_l = 9976.904476606509
   * h_r = 9976.904476606509
   * hu_l = -906.6229611756387
   * hu_r = 906.6229611756387
   * h* = 9974.006714260977
   */

  // construct solver and setup a shock-shock problem
  tsunami_lab::patches::WavePropagation1d m_waveProp(100, true);

  for (std::size_t l_ce = 0; l_ce < 50; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         9976.904476606509);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            -906.6229611756387);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }
  for (std::size_t l_ce = 50; l_ce < 100; l_ce++)
  {
    m_waveProp.setHeight(l_ce,
                         0,
                         9976.904476606509);
    m_waveProp.setMomentumX(l_ce,
                            0,
                            906.6229611756387);
    m_waveProp.setBathymetry(l_ce,
                             0,
                             0);
  }

  // set outflow boundary condition
  m_waveProp.setGhostOutflow();

  // perform a time step
  for (int i = 0; i < 30; i++)
  {
    m_waveProp.timeStep(0.001);
  }

  // test for h*
  REQUIRE(m_waveProp.getHeight()[49] == Approx(9974.006714260977));
  REQUIRE(m_waveProp.getHeight()[50] == Approx(9974.006714260977));
}