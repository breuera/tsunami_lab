/**
 * @author Alexander Breuer (alex.breuer AT uni-jena.de)
 *
 * @section DESCRIPTION
 * IO-routines for writing a snapshot as Comma Separated Values (CSV).
 **/
#ifndef TSUNAMI_LAB_IO_CSV
#define TSUNAMI_LAB_IO_CSV

#include "../constants.h"
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include "rapidcsv.h"
#include "../constants.h"

namespace tsunami_lab
{
  namespace io
  {
    class Csv;
  }
}

class tsunami_lab::io::Csv
{
public:
  /**
   * Writes the data as CSV to the given stream.
   *
   * @param i_dxy cell width in x- and y-direction.
   * @param i_nx number of cells in x-direction.
   * @param i_ny number of cells in y-direction.
   * @param i_stride stride of the data arrays in y-direction (x is assumed to be stride-1).
   * @param i_h water height of the cells; optional: use nullptr if not required.
   * @param i_hu momentum in x-direction of the cells; optional: use nullptr if not required.
   * @param i_hv momentum in y-direction of the cells; optional: use nullptr if not required.
   * @param i_b bathymetry of the cells; optional: use nullptr if not required.
   * @param io_stream stream to which the CSV-data is written.
   **/
  static void write(t_real i_dxy,
                    t_idx i_nx,
                    t_idx i_ny,
                    t_idx i_stride,
                    t_real const *i_h,
                    t_real const *i_hu,
                    t_real const *i_hv,
                    t_real const *i_b,
                    std::ostream &io_stream);

  /**
   * @brief gets rapidcsv::Document and row count from CSV file
   *
   * @param i_filePath path to CSV file
   * @param o_doc csv file as rapidcsv::Document
   * @param o_rowCount row count of csv file
   */
  static void openCSV(const std::string &i_filePath, rapidcsv::Document &o_doc, size_t &o_rowCount);

  /**
   * @brief reads a line from a rapidcsv::Document
   *
   * @param i_doc rapidcsv::Document
   * @param i_row row to read
   * @return t_real value of the line
   */
  static tsunami_lab::t_real readLine(const rapidcsv::Document &i_doc, size_t i_row);
};

#endif