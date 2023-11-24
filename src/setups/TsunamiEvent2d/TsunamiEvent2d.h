/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Two-dimensional Tsunami event setup.
 **/

#ifndef TSUNAMI_LAB_SETUPS_TUSNAMI_EVENT_2D_H
#define TSUNAMI_LAB_SETUPS_TUSNAMI_EVENT_2D_H

#include "../Setup.h"

namespace tsunami_lab {
    namespace setups {
        class TsunamiEvent2d;
    }

}  // namespace tsunami_lab
/**
 * 2d tsunami event setup.
 **/
class tsunami_lab::setups::TsunamiEvent2d : public Setup {
   private:
    //! bathymetry
    t_real *m_bathymetry;

    //! displacement
    t_real *m_displacement;

   public:
    /**
     * Constructor.
     *
     * @param i_bathymetry bathymetry on location (x, y).
     * @param i_displacement displacement on location (x, y).
     **/
    TsunamiEvent2d(t_real *i_bathymetry,
                   t_real *i_displacement);

    /**
     * Gets the height in x-direction.
     *
     * @param in_x x-coordinate of the queried point.
     * @param in_y y-coordinate of the queried point.
     * @return height in x-direction.
     **/
    t_real getHeight(t_real in_x,
                     t_real in_y,
                     t_real) const;

    /**
     * Gets the momentum in x-direction.
     *
     * @param in_x x-coordinate of the queried point.
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
                         t_real in_y,
                         t_real) const;
};

#endif