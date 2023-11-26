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

#include "../../constants.h"
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

    //! raw X pos of bathymetry
    t_real *m_rawX_bathymetry;

    //! dimension of raw X pos of bathymetry
    t_idx m_dimX_bathymetry;

    //! raw Y pos of bathymetry
    t_real *m_rawY_bathymetry;

    //! dimension of raw Y pos of bathymetry
    t_idx m_dimY_bathymetry;

    //! displacement
    t_real *m_displacement;

    //! raw X pos of displacement
    t_real *m_rawX_displacement;

    //! dimension of raw X pos of displacement
    t_idx m_dimX_displacement;

    //! raw Y pos of displacement
    t_real *m_rawY_displacement;

    //! dimension of raw Y pos of displacement
    t_idx m_dimY_displacement;

   public:
    /**
     * Constructor.
     *
     * @param in_bathymetry bathymetry on location (x, y).
     * @param in_rawX_bathymetry raw x values of bathymetry.
     * @param in_dimX_bathymetry dimension of raw x values of bathymetry.
     * @param in_rawY_bathymetry raw y values of bathymetry.
     * @param in_dimY_bathymetry dimension of raw y values of bathymetry.
     * @param in_displacement displacement on location (x, y).
     * @param in_rawX_displacement raw x values of displacement.
     * @param in_dimX_displacement dimension of raw x values of displacement.
     * @param in_rawY_displacement raw y values of displacement.
     * @param in_dimY_displacement dimension of raw y values of displacement.
     *
     **/
    TsunamiEvent2d(t_real *in_bathymetry,
                   t_real *in_rawX_bathymetry,
                   t_idx in_dimX_bathymetry,
                   t_real *in_rawY_bathymetry,
                   t_idx in_dimY_bathymetry,
                   t_real *in_displacement,
                   t_real *in_rawX_displacement,
                   t_idx in_dimX_displacement,
                   t_real *in_rawY_displacement,
                   t_idx in_dimY_displacement);

    /**
     * Gets the height in x-direction.
     *
     * @param in_x x-coordinate of the queried point.
     * @param in_y y-coordinate of the queried point.
     * @return height in x-direction.
     **/
    t_real getHeight(t_real in_x,
                     t_real in_y) const;

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
                         t_real in_y) const;
};

#endif