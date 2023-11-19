#include <catch2/catch.hpp>
#include "WavePropagation2d.h"
#include "../../constants.h"

TEST_CASE("Test the 2d wave propagation fwave-solver x-direction.", "[WaveProp2dFWavedX]")
{
    /*
     * Test case:
     *
     *   Single dam break problem between x-cell 49 and 50.
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
     *
     * Carbon-copy of WavePropagation1d.test, but added second dimension
     */

    int stride = 102;

    tsunami_lab::patches::WavePropagation2d m_waveProp(100,
                                                       100,
                                                       1,
                                                       0,
                                                       0,
                                                       0,
                                                       0);

    for (std::size_t l_cx = 0; l_cx < 50; l_cx++)
    {
        for (std::size_t l_cy = 0; l_cy < 100; l_cy++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 10);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    for (std::size_t l_cx = 50; l_cx < 100; l_cx++)
    {
        for (std::size_t l_cy = 0; l_cy < 100; l_cy++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 8);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    // perform a time step
    m_waveProp.timeStep(0.1);

    // steady state
    for (std::size_t l_cx = 1; l_cx < 50; l_cx++)
    {
        for (std::size_t l_cy = 1; l_cy < 101; l_cy++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(10));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }

    // dam-break
    for (std::size_t l_cy = 1; l_cy < 101; l_cy++)
    {
        REQUIRE(m_waveProp.getHeight()[50 + l_cy * stride] == Approx(10 - 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[50 + l_cy * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getMomentumY()[50 + l_cy * stride] == Approx(0));
        REQUIRE(m_waveProp.getBathymetry()[50 + l_cy * stride] == Approx(0));

        REQUIRE(m_waveProp.getHeight()[51 + l_cy * stride] == Approx(8 + 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[51 + l_cy * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getMomentumY()[51 + l_cy * stride] == Approx(0));
        REQUIRE(m_waveProp.getBathymetry()[51 + l_cy * stride] == Approx(0));
    }

    // steady state
    for (std::size_t l_cx = 52; l_cx < 101; l_cx++)
    {
        for (std::size_t l_cy = 1; l_cy < 101; l_cy++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(8));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }
}

TEST_CASE("Test the 2d wave propagation fwave-solver y-direction.", "[WaveProp2dFWavedY]")
{
    /*
     * Test case:
     *
     *   Single dam break problem between y-cell 49 and 50.
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
     *
     * Carbon-copy of WavePropagation1d.test, but added second dimension
     */

    int stride = 102;

    tsunami_lab::patches::WavePropagation2d m_waveProp(100,
                                                       100,
                                                       1,
                                                       0,
                                                       0,
                                                       0,
                                                       0);

    for (std::size_t l_cy = 0; l_cy < 50; l_cy++)
    {
        for (std::size_t l_cx = 0; l_cx < 100; l_cx++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 10);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    for (std::size_t l_cy = 50; l_cy < 100; l_cy++)
    {
        for (std::size_t l_cx = 0; l_cx < 100; l_cx++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 8);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    // perform a time step
    m_waveProp.timeStep(0.1);

    // steady state
    for (std::size_t l_cy = 1; l_cy < 50; l_cy++)
    {
        for (std::size_t l_cx = 1; l_cx < 101; l_cx++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(10));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }

    // dam-break
    for (std::size_t l_cx = 1; l_cx < 101; l_cx++)
    {
        REQUIRE(m_waveProp.getHeight()[l_cx + 50 * stride] == Approx(10 - 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[l_cx + 50 * stride] == Approx(0));
        REQUIRE(m_waveProp.getMomentumY()[l_cx + 50 * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getBathymetry()[l_cx + 50 * stride] == Approx(0));

        REQUIRE(m_waveProp.getHeight()[l_cx + 51 * stride] == Approx(8 + 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[l_cx + 51 * stride] == Approx(0));
        REQUIRE(m_waveProp.getMomentumY()[l_cx + 51 * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getBathymetry()[l_cx + 51 * stride] == Approx(0));
    }

    // steady state
    for (std::size_t l_cy = 52; l_cy < 101; l_cy++)
    {
        for (std::size_t l_cx = 1; l_cx < 101; l_cx++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(8));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }
}

TEST_CASE("Test the 2d wave propagation roe-solver x-direction.", "[WaveProp2dRoedX]")
{
    /*
     * Test case:
     *
     *   Single dam break problem between x-cell 49 and 50.
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
     *
     * Carbon-copy of WavePropagation1d.test, but added second dimension
     */

    int stride = 102;

    tsunami_lab::patches::WavePropagation2d m_waveProp(100,
                                                       100,
                                                       0,
                                                       0,
                                                       0,
                                                       0,
                                                       0);

    for (std::size_t l_cx = 0; l_cx < 50; l_cx++)
    {
        for (std::size_t l_cy = 0; l_cy < 100; l_cy++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 10);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    for (std::size_t l_cx = 50; l_cx < 100; l_cx++)
    {
        for (std::size_t l_cy = 0; l_cy < 100; l_cy++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 8);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    // perform a time step
    m_waveProp.timeStep(0.1);

    // steady state
    for (std::size_t l_cx = 1; l_cx < 50; l_cx++)
    {
        for (std::size_t l_cy = 1; l_cy < 101; l_cy++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(10));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }

    // dam-break
    for (std::size_t l_cy = 1; l_cy < 101; l_cy++)
    {
        REQUIRE(m_waveProp.getHeight()[50 + l_cy * stride] == Approx(10 - 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[50 + l_cy * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getMomentumY()[50 + l_cy * stride] == Approx(0));
        REQUIRE(m_waveProp.getBathymetry()[50 + l_cy * stride] == Approx(0));

        REQUIRE(m_waveProp.getHeight()[51 + l_cy * stride] == Approx(8 + 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[51 + l_cy * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getMomentumY()[51 + l_cy * stride] == Approx(0));
        REQUIRE(m_waveProp.getBathymetry()[51 + l_cy * stride] == Approx(0));
    }

    // steady state
    for (std::size_t l_cx = 52; l_cx < 101; l_cx++)
    {
        for (std::size_t l_cy = 1; l_cy < 101; l_cy++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(8));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }
}

TEST_CASE("Test the 2d wave propagation roe-solver y-direction.", "[WaveProp2dRoeY]")
{
    /*
     * Test case:
     *
     *   Single dam break problem between y-cell 49 and 50.
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
     *
     * Carbon-copy of WavePropagation1d.test, but added second dimension
     */

    int stride = 102;

    tsunami_lab::patches::WavePropagation2d m_waveProp(100,
                                                       100,
                                                       0,
                                                       0,
                                                       0,
                                                       0,
                                                       0);

    for (std::size_t l_cy = 0; l_cy < 50; l_cy++)
    {
        for (std::size_t l_cx = 0; l_cx < 100; l_cx++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 10);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    for (std::size_t l_cy = 50; l_cy < 100; l_cy++)
    {
        for (std::size_t l_cx = 0; l_cx < 100; l_cx++)
        {
            m_waveProp.setHeight(l_cx,
                                 l_cy,
                                 8);
            m_waveProp.setMomentumX(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setMomentumY(l_cx,
                                    l_cy,
                                    0);
            m_waveProp.setBathymetry(l_cx,
                                     l_cy,
                                     0);
        }
    }

    // perform a time step
    m_waveProp.timeStep(0.1);

    // steady state
    for (std::size_t l_cy = 1; l_cy < 50; l_cy++)
    {
        for (std::size_t l_cx = 1; l_cx < 101; l_cx++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(10));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }

    // dam-break
    for (std::size_t l_cx = 1; l_cx < 101; l_cx++)
    {
        REQUIRE(m_waveProp.getHeight()[l_cx + 50 * stride] == Approx(10 - 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[l_cx + 50 * stride] == Approx(0));
        REQUIRE(m_waveProp.getMomentumY()[l_cx + 50 * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getBathymetry()[l_cx + 50 * stride] == Approx(0));

        REQUIRE(m_waveProp.getHeight()[l_cx + 51 * stride] == Approx(8 + 0.1 * 9.394671362));
        REQUIRE(m_waveProp.getMomentumX()[l_cx + 51 * stride] == Approx(0));
        REQUIRE(m_waveProp.getMomentumY()[l_cx + 51 * stride] == Approx(0 + 0.1 * 88.25985));
        REQUIRE(m_waveProp.getBathymetry()[l_cx + 51 * stride] == Approx(0));
    }

    // steady state
    for (std::size_t l_cy = 52; l_cy < 101; l_cy++)
    {
        for (std::size_t l_cx = 1; l_cx < 101; l_cx++)
        {
            REQUIRE(m_waveProp.getHeight()[l_cx + l_cy * stride] == Approx(8));
            REQUIRE(m_waveProp.getMomentumX()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getMomentumY()[l_cx + l_cy * stride] == Approx(0));
            REQUIRE(m_waveProp.getBathymetry()[l_cx + l_cy * stride] == Approx(0));
        }
    }
}