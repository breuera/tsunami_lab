/**
 * @author Phillip Rothenbeck (phillip.rothenbeck AT uni-jena.de)
 * @author Moritz Rätz (moritz.raetz AT uni-jena.de)
 * @author Marek Sommerfeld (marek.sommerfeld AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for reading and writing NetCDF files.
 **/

#include "NetCDF.h"

#include <iostream>

int tsunami_lab::io::NetCDF::read(std::string i_nameBathymetry,
                                  std::string i_nameDisplacements,
                                  t_idx *o_bathymetryDimX,
                                  t_idx *o_bathymetryDimY,
                                  t_real *&o_bathymetryPosX,
                                  t_real *&o_bathymetryPosY,
                                  t_real *&o_bathymetry,
                                  t_idx *o_dispDimX,
                                  t_idx *o_dispDimY,
                                  t_real *&o_dispPosX,
                                  t_real *&o_dispPosY,
                                  t_real *&o_displacements) {
    // add res path
    i_nameBathymetry = "./res/" + i_nameBathymetry;
    i_nameDisplacements = "./res/" + i_nameDisplacements;
    int l_ncIDBathymetry, l_ncIDDisplacements;

    std::cout << "start loading bathymetry file: " << i_nameBathymetry << std::endl;
    int l_nc_err = nc_open(i_nameBathymetry.c_str(), 0, &l_ncIDBathymetry);

    // open bathymetry file
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not open file: " << i_nameBathymetry << std::endl;
        return 1;
    }

    // read bathymetry
    // get dimensions
    std::size_t l_xDim, l_yDim;
    l_nc_err = nc_inq_dimlen(l_ncIDBathymetry, 0, &l_xDim);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not get the size of the x-dimension in bathymetry." << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_dimlen(l_ncIDBathymetry, 1, &l_yDim);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not get the size of the y-dimension in bathymetry." << std::endl;
        return 1;
    }

    *o_bathymetryDimX = (t_idx)l_xDim;
    *o_bathymetryDimY = (t_idx)l_yDim;
    o_bathymetry = new tsunami_lab::t_real[l_xDim * l_yDim];
    o_bathymetryPosX = new tsunami_lab::t_real[l_xDim];
    o_bathymetryPosY = new tsunami_lab::t_real[l_yDim];

    // get variable ids
    int l_varIDx, l_varIDy, l_varIDz;
    l_nc_err = nc_inq_varid(l_ncIDBathymetry, "x", &l_varIDx);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not find the x variable in bathymetry." << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(l_ncIDBathymetry, "y", &l_varIDy);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not find the y-variable in bathymetry." << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(l_ncIDBathymetry, "z", &l_varIDz);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not find the z-variable in bathymetry." << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDBathymetry, l_varIDx, &o_bathymetryPosX[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable x" << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDBathymetry, l_varIDy, &o_bathymetryPosY[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable y" << std::endl;
        return 1;
    }
    std::cout << "finished bathymetry configuration loading" << std::endl;

    // read bathymetry
    std::cout << "loading bathymetry data" << std::endl;
    l_nc_err = nc_get_var_float(l_ncIDBathymetry, l_varIDz, &o_bathymetry[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable z" << std::endl;
        return 1;
    }

    std::cout << "finished loading bathymetry file: " << i_nameBathymetry << std::endl;
    // read displacements

    std::cout << "start loading displacement file: " << i_nameDisplacements << std::endl;
    l_nc_err = nc_open(i_nameDisplacements.c_str(), 0, &l_ncIDDisplacements);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not open file: " << i_nameDisplacements << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_dimlen(l_ncIDDisplacements, 0, &l_xDim);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not get the size of the x-dimension in displacements." << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_dimlen(l_ncIDDisplacements, 1, &l_yDim);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not get the size of the y-dimension in displacements." << std::endl;
        return 1;
    }

    *o_dispDimX = (t_idx)l_xDim;
    *o_dispDimY = (t_idx)l_yDim;
    o_displacements = new tsunami_lab::t_real[l_xDim * l_yDim];
    o_dispPosX = new tsunami_lab::t_real[l_xDim];
    o_dispPosY = new tsunami_lab::t_real[l_yDim];

    // get variable ids
    l_nc_err = nc_inq_varid(l_ncIDDisplacements, "x", &l_varIDx);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not find x-variable in displacements." << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(l_ncIDDisplacements, "y", &l_varIDy);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not find y-variable in displacements." << std::endl;
        return 1;
    }

    l_nc_err = nc_inq_varid(l_ncIDDisplacements, "z", &l_varIDz);

    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not find z-variable in displacements." << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDDisplacements, l_varIDx, &o_dispPosX[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable x" << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncIDDisplacements, l_varIDy, &o_dispPosY[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable y" << std::endl;
        return 1;
    }

    // read displacements
    std::cout << "loading displacements data" << std::endl;
    l_nc_err = nc_get_var_float(l_ncIDDisplacements, l_varIDz, &o_displacements[0]);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not load data from variable z" << std::endl;
        return 1;
    }
    std::cout << "finished loading displacement file: " << i_nameDisplacements << std::endl;

    return 0;
}

int tsunami_lab::io::NetCDF::init(t_idx i_currentFrame) {
    int l_nc_err = 0;

    // define dimensions
    l_nc_err = nc_def_dim(m_ncId, "x", m_nx, &m_dimXId);
    l_nc_err += nc_def_dim(m_ncId, "y", m_ny, &m_dimYId);
    l_nc_err += nc_def_dim(m_ncId, "time", i_currentFrame, &m_dimTimeId);
    l_nc_err += nc_def_dim(m_ncId, "simTime", 1, &m_dimSimTimeId);
    l_nc_err += nc_def_dim(m_ncId, "endTime", 1, &m_dimEndTimeId);
    l_nc_err += nc_def_dim(m_ncId, "frame", 1, &m_dimFrameId);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "NCError: Define dimensions." << std::endl;
        return 1;
    }

    // define variables
    l_nc_err = nc_def_var(m_ncId, "x", NC_FLOAT, 1, &m_dimXId, &m_varXId);
    l_nc_err += nc_put_att_text(m_ncId, m_varXId, "units", 6, "meters");
    l_nc_err += nc_put_att_text(m_ncId, m_varXId, "axis", 1, "X");

    l_nc_err += nc_def_var(m_ncId, "y", NC_FLOAT, 1, &m_dimYId, &m_varYId);
    l_nc_err += nc_put_att_text(m_ncId, m_varYId, "units", 6, "meters");
    l_nc_err += nc_put_att_text(m_ncId, m_varXId, "axis", 1, "Y");

    l_nc_err += nc_def_var(m_ncId, "time", NC_FLOAT, 1, &m_dimTimeId, &m_varTimeId);
    l_nc_err += nc_put_att_text(m_ncId, m_varTimeId, "units", 7, "seconds");

    int l_dimBathymetryIds[2] = {m_dimYId, m_dimXId};
    l_nc_err += nc_def_var(m_ncId, "bathymetry", NC_FLOAT, 2, l_dimBathymetryIds, &m_varBathymetryId);
    l_nc_err += nc_put_att_text(m_ncId, m_varBathymetryId, "units", 6, "meters");

    int l_dimHeightIds[3] = {m_dimTimeId, m_dimYId, m_dimXId};
    l_nc_err += nc_def_var(m_ncId, "height", NC_FLOAT, 3, l_dimHeightIds, &m_varHeightId);
    l_nc_err += nc_put_att_text(m_ncId, m_varHeightId, "units", 6, "meters");

    int l_dimMomentumXIds[3] = {m_dimTimeId, m_dimYId, m_dimXId};
    l_nc_err += nc_def_var(m_ncId, "momentum_x", NC_FLOAT, 3, l_dimMomentumXIds, &m_varMomentumXId);
    l_nc_err += nc_put_att_text(m_ncId, m_varMomentumXId, "units", 11, "meters*kg/s");

    int l_dimMomentumYIds[3] = {m_dimTimeId, m_dimYId, m_dimXId};
    l_nc_err += nc_def_var(m_ncId, "momentum_y", NC_FLOAT, 3, l_dimMomentumYIds, &m_varMomentumYId);
    l_nc_err += nc_put_att_text(m_ncId, m_varMomentumYId, "units", 11, "meters*kg/s");

    l_nc_err += nc_def_var(m_ncId, "simTime", NC_FLOAT, 1, &m_dimSimTimeId, &m_varSimTimeId);
    l_nc_err += nc_def_var(m_ncId, "endTime", NC_FLOAT, 1, &m_dimEndTimeId, &m_varEndTimeId);
    l_nc_err += nc_def_var(m_ncId, "frame", NC_FLOAT, 1, &m_dimFrameId, &m_varFrameId);

    l_nc_err += nc_enddef(m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "NCError: Define variables." << std::endl;
        return 1;
    }

    return NC_NOERR;
}

int tsunami_lab::io::NetCDF::store(t_real i_simTime,
                                   t_idx i_frame,
                                   t_real const *i_h,
                                   t_real const *i_hu,
                                   t_real const *i_hv) {
    m_time[i_frame] = i_simTime;

    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
            t_real l_h = i_h[(l_iy + 1) * m_stride + (l_ix + 1)];
            t_real l_b = m_dataB[l_iy * m_nx + l_ix];
            m_height[l_ix + l_iy * m_nx + m_nxy * i_frame] = l_h + l_b;
            m_momentumX[l_ix + l_iy * m_nx + m_nxy * i_frame] = i_hu[(l_iy + 1) * m_stride + (l_ix + 1)];
            m_momentumY[l_ix + l_iy * m_nx + m_nxy * i_frame] = i_hv[(l_iy + 1) * m_stride + (l_ix + 1)];
        }
    }

    return 0;
}

int tsunami_lab::io::NetCDF::write(t_idx i_currentFrame,
                                   std::string i_checkPointPath = "",
                                   t_real i_simTime = -1,
                                   t_real i_endTime = -1) {
    int l_nc_err = 0;

    // create netCDF file
    std::string l_outFileName;
    if (i_checkPointPath.compare("") != 0) {
        l_outFileName = i_checkPointPath;
    } else {
        l_outFileName = m_outFileName;
    }
    std::cout << l_outFileName << std::endl;
    l_nc_err += nc_create((l_outFileName).c_str(), NC_CLOBBER, &m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "NCError: Create file." << std::endl;
        return 1;
    }

    // define dims and vars
    init(i_currentFrame);

    // write data
    l_nc_err = nc_put_var_float(m_ncId, m_varXId, m_dataX);
    l_nc_err += nc_put_var_float(m_ncId, m_varYId, m_dataY);
    l_nc_err += nc_put_var_float(m_ncId, m_varBathymetryId, m_dataB);
    l_nc_err += nc_put_var_float(m_ncId, m_varTimeId, m_time);
    l_nc_err += nc_put_var_float(m_ncId, m_varHeightId, m_height);
    l_nc_err += nc_put_var_float(m_ncId, m_varMomentumXId, m_momentumX);
    l_nc_err += nc_put_var_float(m_ncId, m_varMomentumYId, m_momentumY);

    l_nc_err += nc_put_var_float(m_ncId, m_varSimTimeId, &i_simTime);
    l_nc_err += nc_put_var_float(m_ncId, m_varEndTimeId, &i_endTime);
    unsigned long long l_currentFrame = i_currentFrame;
    l_nc_err += nc_put_var_ulonglong(m_ncId, m_varFrameId, &l_currentFrame);
    if (l_nc_err != NC_NOERR) {
        std::cout << "NCError: Put variables." << std::endl;
        return 1;
    }

    l_nc_err = nc_close(m_ncId);
    if (l_nc_err != NC_NOERR) {
        std::cout << "NCError: Close file." << std::endl;
        return 1;
    }

    return NC_NOERR;
}

int tsunami_lab::io::NetCDF::write() {
    return write(m_frameCount);
}

int tsunami_lab::io::NetCDF::readCheckpoint(std::string i_checkPoinPath,
                                            t_real *o_height,
                                            t_real *o_momentumX,
                                            t_real *o_momentumY,
                                            t_real *o_bathymetry,
                                            t_real *o_time,
														  t_idx *o_currentFrame,
                                            t_real *o_endSimTime,
                                            t_real *o_startSimTime) {
    int l_ncID;
    // open checkpoint file
    int l_nc_err = nc_open(i_checkPoinPath.c_str(), 0, &l_ncID);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "Could not open file: " << i_checkPoinPath << std::endl;
        return 1;
    }

    // get dimensions
    std::size_t l_xDim, l_yDim, l_timeDim;
	 std::size_t l_simTimeDim, l_endTimeDim, l_frameDim;

    l_nc_err = nc_inq_dimlen(l_ncID, 0, &l_xDim);
    l_nc_err += nc_inq_dimlen(l_ncID, 1, &l_yDim);
    l_nc_err += nc_inq_dimlen(l_ncID, 2, &l_timeDim);

    l_nc_err += nc_inq_dimlen(l_ncID, 3, &l_simTimeDim);
    l_nc_err += nc_inq_dimlen(l_ncID, 4, &l_endTimeDim);
    l_nc_err += nc_inq_dimlen(l_ncID, 5, &l_frameDim);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "NCError: Load Dimensions." << std::endl;
        return 1;
    }

    o_time = new tsunami_lab::t_real[l_timeDim];
    o_height = new tsunami_lab::t_real[l_xDim * l_yDim * l_timeDim];
    o_momentumX = new tsunami_lab::t_real[l_xDim * l_yDim * l_timeDim];
    o_momentumY = new tsunami_lab::t_real[l_xDim * l_yDim * l_timeDim];
    o_bathymetry = new tsunami_lab::t_real[l_xDim * l_yDim];

    // get variable ids
    int l_varIDtime, l_varIDheight, l_varIDmomentumX, l_varIDmomentumY, l_varIDbathymetry;
	 int l_varIDsimTime, l_varIDendTime, l_varIDframe;
    
    l_nc_err += nc_inq_varid(l_ncID, "time", &l_varIDtime);
    l_nc_err += nc_inq_varid(l_ncID, "height", &l_varIDheight);
    l_nc_err += nc_inq_varid(l_ncID, "momentumX", &l_varIDmomentumX);
    l_nc_err += nc_inq_varid(l_ncID, "momentumY", &l_varIDmomentumY);
    l_nc_err += nc_inq_varid(l_ncID, "bathymetry", &l_varIDbathymetry);

	 l_nc_err += nc_inq_varid(l_ncID, "simTime", &l_varIDsimTime);
    l_nc_err += nc_inq_varid(l_ncID, "endTime", &l_varIDendTime);
    l_nc_err += nc_inq_varid(l_ncID, "frame", &l_varIDframe);
    if (l_nc_err != NC_NOERR) {
        std::cerr << "NCError: Load Variable IDs" << std::endl;
        return 1;
    }

    l_nc_err = nc_get_var_float(l_ncID, l_varIDtime, o_time);
    l_nc_err += nc_get_var_float(l_ncID, l_varIDheight, o_height);
    l_nc_err += nc_get_var_float(l_ncID, l_varIDmomentumX, o_momentumX);
    l_nc_err += nc_get_var_float(l_ncID, l_varIDmomentumY, o_momentumY);
    l_nc_err += nc_get_var_float(l_ncID, l_varIDbathymetry, o_bathymetry);

    l_nc_err += nc_get_var_float(l_ncID, l_varIDsimTime, o_startSimTime);
    l_nc_err += nc_get_var_float(l_ncID, l_varIDendTime, o_endSimTime);
	 unsigned long long l_currentFrame;
    l_nc_err += nc_get_var_ulonglong(l_ncID, l_varIDframe, &l_currentFrame);
	 *o_currentFrame = (t_idx)l_currentFrame;
    if (l_nc_err != NC_NOERR) {
        std::cerr << "NCError: Load Data" << std::endl;
        return 1;
    }

	 return 0;
}

tsunami_lab::io::NetCDF::NetCDF(t_real i_endTime,
                                t_real i_dt,
                                t_idx i_timeStepsPerFrame,
                                t_real i_dxy,
                                t_idx i_nx,
                                t_idx i_ny,
                                t_idx i_stride,
                                t_real const *i_b,
                                std::string i_outFileName) {
    m_dxy = i_dxy;
    m_nx = i_nx;
    m_ny = i_ny;
    m_nxy = i_nx * i_ny;
    m_stride = i_stride;
    m_outFileName = i_outFileName;

    m_frameCount = ceil((i_endTime / i_dt) / i_timeStepsPerFrame);
    m_dataSize = m_nxy * m_frameCount;

    m_time = new t_real[m_frameCount];
    m_height = new t_real[m_dataSize];
    m_momentumX = new t_real[m_dataSize];
    m_momentumY = new t_real[m_dataSize];

    m_dataX = new t_real[m_nx];
    m_dataY = new t_real[m_ny];
    m_dataB = new t_real[m_nxy];

    for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
        m_dataX[l_ix] = (l_ix + 0.5) * m_dxy;
    }
    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        m_dataY[l_iy] = (l_iy + 0.5) * m_dxy;
    }
    for (t_idx l_iy = 0; l_iy < m_ny; l_iy++) {
        for (t_idx l_ix = 0; l_ix < m_nx; l_ix++) {
            m_dataB[l_ix + l_iy * m_nx] = i_b[(l_iy + 1) * m_stride + (l_ix + 1)];
        }
    }
}

tsunami_lab::io::NetCDF::~NetCDF() {
    delete[] m_time;

    delete[] m_height;
    delete[] m_momentumX;
    delete[] m_momentumY;

    delete[] m_dataX;
    delete[] m_dataY;
    delete[] m_dataB;
}
