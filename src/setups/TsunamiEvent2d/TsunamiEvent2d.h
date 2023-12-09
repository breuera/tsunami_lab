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
    //! length of the simulation in x-direction.
    t_real m_simLenX = 0;

    //! length of the simulation in y-direction.
    t_real m_simLenY = 0;

    //! bathymetries
    t_real *m_bathymetry = nullptr;

    //! dimension of raw x-coordinates of bathymetry
    t_idx m_bathymetryDimX = 0;

    //! dimension of raw y-coordinates of bathymetry
    t_idx m_bathymetryDimY = 0;

    //! raw x-coordinates of the bathymetry
    t_real *m_bathymetryPosX = nullptr;

    //! raw y-coordinates of the bathymetry
    t_real *m_bathymetryPosY = nullptr;

    //! displacements
    t_real *m_displacement = nullptr;

    //! dimension of raw x-coordinates of displacements
    t_idx m_displacementsDimX = 0;

    //! dimension of raw y-coordinates of displacements
    t_idx m_displacementsDimY = 0;

    //! raw x-coordinates of the displacements
    t_real *m_displacementsPosX = nullptr;

    //! raw y-coordinates of the displacements
    t_real *m_displacementsPosY = nullptr;

    //! epicenter offset to 0-point in x-direction
    t_real m_epicenterOffsetX = 0;

    //! epicenter offset to 0-point in y-direction
    t_real m_epicenterOffsetY = 0;

    //! delta
    t_real m_delta = 20;

   public:
    /**
     * Construct.
     *
     * @param i_simLenX length of the simulation in x-direction.
     * @param i_simLenY length of the simulation in y-direction.
     * @param i_bathymetryDimX dimension of raw x-coordinates of bathymetry.
     * @param i_bathymetryDimY dimension of raw y-coordinates of bathymetry.
     * @param i_bathymetryPosX raw x-coordinates of the bathymetry.
     * @param i_bathymetryPosY raw y-coordinates of the bathymetry.
     * @param i_bathymetry bathymetries.
     * @param i_displacementsDimX dimension of raw x-coordinates of displacements.
     * @param i_displacementsDimY dimension of raw y-coordinates of displacements.
     * @param i_displacementsPosX raw x-coordinates of the displacements.
     * @param i_displacementsPosY raw y-coordinates of the displacements.
     * @param i_displacements displacements.
     * @param i_epicenterOffsetX epicenter offset to 0-point in x-direction
     * @param i_epicenterOffsetY epicenter offset to 0-point in y-direction
     */
    TsunamiEvent2d(t_real i_simLenX,
                   t_real i_simLenY,
                   t_idx i_bathymetryDimX,
                   t_idx i_bathymetryDimY,
                   t_real *i_bathymetryPosX,
                   t_real *i_bathymetryPosY,
                   t_real *i_bathymetry,
                   t_idx i_displacementsDimX,
                   t_idx i_displacementsDimY,
                   t_real *i_displacementsPosX,
                   t_real *i_displacementsPosY,
                   t_real *i_displacements,
                   t_real i_epicenterOffsetX,
                   t_real i_epicenterOffsetY);

    /**
     * Destructor.
     */
    ~TsunamiEvent2d();

    /**
     * Gets the height in x-direction.
     *
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return height in x-direction.
     **/
    t_real getHeight(t_real i_x,
                     t_real i_y) const;

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
     * @param i_x x-coordinate of the queried point.
     * @param i_y y-coordinate of the queried point.
     * @return bathymetry at the given point.
     **/
    t_real getBathymetry(t_real i_x,
                         t_real i_y) const;
};

#endif