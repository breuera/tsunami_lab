/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Unit tests for the CSV-interface.
 **/
#include <catch2/catch.hpp>
#include "../constants.h"
#include <sstream>
#include <fstream>
#define private public
#include "Csv.h"
#undef public

TEST_CASE("Test the CSV-writer for 1D settings.", "[CsvWrite1d]")
{
  // define a simple example
  tsunami_lab::t_real l_h[7] = {0, 1, 2, 3, 4, 5, 6};
  tsunami_lab::t_real l_hu[7] = {6, 5, 4, 3, 2, 1, 0};

  std::stringstream l_stream0;
  tsunami_lab::io::Csv::write(0.5,
                              5,
                              1,
                              7,
                              l_h + 1,
                              l_hu + 1,
                              nullptr,
                              l_stream0);

  std::string l_ref0 = R"V0G0N(x,y,height,momentum_x
0.25,0.25,1,5
0.75,0.25,2,4
1.25,0.25,3,3
1.75,0.25,4,2
2.25,0.25,5,1
)V0G0N";

  REQUIRE(l_stream0.str().size() == l_ref0.size());
  REQUIRE(l_stream0.str() == l_ref0);
}

TEST_CASE("Test the CSV-writer for 2D settings.", "[CsvWrite2d]")
{
  // define a simple example
  tsunami_lab::t_real l_h[16] = {0, 1, 2, 3,
                                 4, 5, 6, 7,
                                 8, 9, 10, 11,
                                 12, 13, 14, 15};
  tsunami_lab::t_real l_hu[16] = {15, 14, 13, 12,
                                  11, 10, 9, 8,
                                  7, 6, 5, 4,
                                  3, 2, 1, 0};
  tsunami_lab::t_real l_hv[16] = {0, 4, 8, 12,
                                  1, 5, 9, 13,
                                  2, 6, 10, 14,
                                  3, 7, 11, 15};

  std::stringstream l_stream1;
  tsunami_lab::io::Csv::write(10,
                              2,
                              2,
                              4,
                              l_h + 4 + 1,
                              l_hu + 4 + 1,
                              l_hv + 4 + 1,
                              l_stream1);

  std::string l_ref1 = R"V0G0N(x,y,height,momentum_x,momentum_y
5,5,5,10,5
15,5,6,9,9
5,15,9,6,6
15,15,10,5,10
)V0G0N";

  REQUIRE(l_stream1.str().size() == l_ref1.size());
  REQUIRE(l_stream1.str() == l_ref1);
}

TEST_CASE("Test the CSV-middle-state-reader.", "[CsvRead]")
{
  // setup reader stream
  std::ifstream l_stream;
  l_stream.open("./res/dummy_middle_states.csv", std::fstream::in);

  // check if file was load
  REQUIRE(!l_stream.fail());

  // initialize arrays
  float *l_hL;
  float *l_huL;
  float *l_hR;
  float *l_huR;
  float *l_hStar;

  tsunami_lab::io::Csv::read_middle_states(l_stream,
                                           l_hL,
                                           l_huL,
                                           l_hR,
                                           l_huR,
                                           l_hStar);

  REQUIRE(l_hL[0] == Approx(8899.326826472694));
  REQUIRE(l_hR[0] == Approx(8899.326826472694));
  REQUIRE(l_huL[0] == Approx(122.0337839252433));
  REQUIRE(l_huR[0] == Approx(-122.0337839252433));
  REQUIRE(l_hStar[0] == Approx(8899.739847378269));

  REQUIRE(l_hL[1] == Approx(9894.065328676988));
  REQUIRE(l_hR[1] == Approx(9894.065328676988));
  REQUIRE(l_huL[1] == Approx(763.616897222239));
  REQUIRE(l_huR[1] == Approx(-763.616897222239));
  REQUIRE(l_hStar[1] == Approx(9896.516538751875));

  REQUIRE(l_hL[9] == Approx(10539.5774699817));
  REQUIRE(l_hR[9] == Approx(10539.5774699817));
  REQUIRE(l_huL[9] == Approx(-988.5578370907829));
  REQUIRE(l_huR[9] == Approx(988.5578370907829));
  REQUIRE(l_hStar[9] == Approx(10536.50332526859));
  free(l_hL);
  free(l_huL);
  free(l_hR);
  free(l_huR);
  free(l_hStar);
}