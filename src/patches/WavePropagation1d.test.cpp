/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests for the one-dimensional wave propagation patch.
 **/
#include <catch2/catch.hpp>
#include "WavePropagation1d.h"
#include "../constants.h"

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
  tsunami_lab::patches::WavePropagation1d m_waveProp(100, false, tsunami_lab::t_boundary::OPEN, tsunami_lab::t_boundary::OPEN);

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
  tsunami_lab::patches::WavePropagation1d m_waveProp(100, true, tsunami_lab::t_boundary::OPEN, tsunami_lab::t_boundary::OPEN);

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

TEST_CASE("Test the 1d wave propagation FWave solver middleStates.csv .", "[WaveProp1dFWavemiddleStatesCsv]")
{
  /**
   * @brief test steady state from middle_states.csv in the Shock-Shock Problem
   * (Riemann Solutions obtained by Alexander Breuer)
   *
   * testing first 10 lines of middle_states.csv
   */

  // construct solver and setup a shock-shock problem
  float testCases[10][5] = {
      {8899.326826472694, 8899.326826472694, 122.0337839252433, -122.0337839252433, 8899.739847378269},
      {9894.065328676988, 9894.065328676988, 763.616897222239, -763.616897222239, 9896.516538751875},
      {1387.176994373967, 1387.176994373967, -101.9619713277172, 101.9619713277172, 1386.303079031417},
      {9976.904476606509, 9976.904476606509, -906.6229611756387, 906.6229611756387, 9974.006714260977},
      {6907.360046520149, 6907.360046520149, -180.6064611678331, 180.6064611678331, 6906.666250464617},
      {1065.53384380855, 1065.53384380855, 64.19327065348772, -64.19327065348772, 1066.161808657808},
      {3042.136044684769, 3042.136044684769, -27.52440428024561, 27.52440428024561, 3041.976718035753},
      {5973.686834276039, 5973.686834276039, 417.2334213893989, -417.2334213893989, 5975.410506492273},
      {10458.94716344883, 10458.94716344883, -366.1438461063776, 366.1438461063776, 10457.80412356421},
      {10539.5774699817, 10539.5774699817, -988.5578370907829, 988.5578370907829, 10536.50332526859}};

  for (int i = 0; i < 10; ++i)
  {
    tsunami_lab::patches::WavePropagation1d m_waveProp(100, true, tsunami_lab::t_boundary::OPEN, tsunami_lab::t_boundary::OPEN);

    for (std::size_t l_ce = 0; l_ce < 50; ++l_ce)
    {
      m_waveProp.setHeight(l_ce,
                           0,
                           testCases[i][0]);
      m_waveProp.setMomentumX(l_ce,
                              0,
                              testCases[i][2]);
      m_waveProp.setBathymetry(l_ce,
                               0,
                               0);
    }
    for (std::size_t l_ce = 50; l_ce < 100; l_ce++)
    {
      m_waveProp.setHeight(l_ce,
                           0,
                           testCases[i][1]);
      m_waveProp.setMomentumX(l_ce,
                              0,
                              testCases[i][3]);
      m_waveProp.setBathymetry(l_ce,
                               0,
                               0);
    }

    // set outflow boundary condition
    m_waveProp.setGhostOutflow();

    // perform a time step
    for (int i = 0; i < 100; i++)
    {
      // set outflow boundary condition
      m_waveProp.setGhostOutflow();

      m_waveProp.timeStep(0.001);
    }

    // test for h*
    REQUIRE(m_waveProp.getHeight()[49] == Approx(testCases[i][4]));
    REQUIRE(m_waveProp.getHeight()[50] == Approx(testCases[i][4]));
  }
}
