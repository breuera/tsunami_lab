/**
 * @author Bohdan Babii, Phillip Rothenbeck
 *
 * @section DESCRIPTION
 * One-dimenstional setup for supercritical Flow
 **/
#ifndef TSUNAMI_LAB_SETUPS_SUPERCRITICAL_FLOW_1D_H
#define TSUNAMI_LAB_SETUPS_SUPERCRITICAL_FLOW_1D_H

#include "../Setup.h"

namespace tsunami_lab {
    namespace setups {
        class SupercriticalFlow1d;
    }
}  // namespace tsunami_lab

class tsunami_lab::setups::SupercriticalFlow1d : public Setup {
   private:
    //! momentum of every cell
    t_real m_hu = 0;

   public:
    /**
     * Constructor.
     *
     * @param i_hu momentum of the cells.
     **/
    SupercriticalFlow1d(t_real i_hu);

    /**
     * Gets the water height at a given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @return height at the given point.
     **/
    t_real getHeight(t_real i_x,
                     t_real) const;

    /**
     * Gets the momentum in x-direction.
     *
     * @param i_x x-coordinate of the queried point.
     * @return momentum in x-direction.
     **/
    t_real getMomentumX(t_real,
                        t_real) const;

    /**
     * Gets the momentum in y-direction.
     *
     * @return momentum in y-direction.
     **/
    t_real getMomentumY(t_real,
                        t_real) const;

    /**
     * Gets the bathymetry at given point.
     *
     * @param i_x x-coordinate of the queried point.
     * @return bathymetry.
     */
    t_real getBathymetry(t_real i_x,
                         t_real) const;
};
#endif