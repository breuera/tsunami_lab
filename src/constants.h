/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * Constants / typedefs used throughout the code.
 **/
#ifndef TSUNAMI_LAB_CONSTANTS_H
#define TSUNAMI_LAB_CONSTANTS_H
#define C_PI 3.14159265358979323846 /* pi */

#include <cstddef>

namespace tsunami_lab {
    //! integral type for cell-ids, pointer arithmetic, etc.
    typedef std::size_t t_idx;

    //! floating point type
    typedef float t_real;
}  // namespace tsunami_lab

#endif