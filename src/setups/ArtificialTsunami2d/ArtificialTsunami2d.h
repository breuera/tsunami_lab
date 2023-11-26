/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Artificial 2d Tsunami setup.
 **/

#ifndef TSUNAMI_LAB_SETUPS_ARTIFICIAL_TSUNAMI_2D_H
#define TSUNAMI_LAB_SETUPS_ARTIFICIAL_TSUNAMI_2D_H

#include "../Setup.h"

namespace tsunami_lab {
    namespace setups {
        class ArtificialTsunami2d;
    }

}  // namespace tsunami_lab
/**
 * 2d artificial tsunami setup.
 **/
class tsunami_lab::setups::ArtificialTsunami2d : public Setup {
   private:
    //! length of simulation in meters in x direction
    t_real m_simLenX = 0;

    //! length of simulation in meters in y direction
    t_real m_simLenY = 0;

   public:
    /**
     * Constructor.
     *
     * @param in_simLenX length of simulation in x direction.
     * @param in_simLenY length of simulation in y direction.
     **/
    ArtificialTsunami2d(t_real in_simLenX,
                        t_real in_simLenY);

    /**
     * Gets the height in x-direction.
     *
     * @return height in x-direction.
     **/
    t_real getHeight(t_real,
                     t_real) const;

    /**
     * Gets the momentum in x-direction.
     *
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
     * Gets the bathymetry at a given point.
     *
     * @param in_x x-coordinate of the queried point.
     * @param in_y y-coordinate of the queried point.
     * @return bathymetry at the given point.
     **/
    t_real getBathymetry(t_real in_x,
                         t_real in_y) const;
};

#endif