#ifndef TSUNAMI_LAB_SOLVERS_FWAVE
#define TSUNAMI_LAB_SOLVERS_FWAVE

#include "../constants.h"

namespace tsunami_lab {
  namespace solvers {
    class fwave;
  }
}

class tsunami_lab::solvers::fwave {
  private:
    static t_real constexpr g = 9.80665;
    static void eigenwerte( t_real   i_hL,
                            t_real   i_hR,
                            t_real   i_uL,
                            t_real   i_uR,
                            t_real & o_waveSpeedL,
                            t_real & o_waveSpeedR );

    static void flux( t_real i_hL,
                      t_real i_hR,
                      t_real i_huL,
                      t_real i_huR,
                      t_real* & o_fdelta);

    static void inverseMatrix(t_real i_eigen1,
                              t_real i_eigen2,
                              t_real o_inverse[4]);
  public:
    static void netUpdates( t_real i_eigen1,
                            t_real i_eigen2,
                            t_real o_inverse[4]);                               
};

#endif