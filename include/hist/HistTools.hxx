/// ===========================================================================
/*! \file   HistTools.hxx
 *  \author Derek Anderson
 *  \date   10.24.2024
 *
 *  Useful tools related to histograms.
 */
/// ===========================================================================

#ifndef RAU_HISTTOOLS_HXX
#define RAU_HISTTOOLS_HXX

// c++ utilities
#include <algorithm>
#include <cassert>
#include <cmath>
#include <optional>
#include <vector>
// root libraries
#include <TMath.h>



namespace ROOTAnalysisUtilities {
  namespace Tools {

    // ------------------------------------------------------------------------
    //! Wrapper function for std::pow
    // ------------------------------------------------------------------------
    double Exponentiate(const double arg, const double base = TMath::E()) {

      return std::pow(base, arg);

    }  // end 'Exponentiate(double)'



    // ------------------------------------------------------------------------
    //! Wrapper function for std::log
    // ------------------------------------------------------------------------
    double Log(const double arg, const double base = TMath::E()) {

      return std::log(arg) / std::log(base);

    }  // end 'Log(double, double)'



    // ------------------------------------------------------------------------
    //! Helper method to divide a range into a certain number of bins
    // ------------------------------------------------------------------------
    std::vector<double> GetBinEdges(
      const uint32_t num,
      const double start,
      const double stop
    ) {

      // throw error if start/stop are out of order
      // or if num is zero
      if (num <= 0)     assert(num > 0);
      if (start > stop) assert(start <= stop);

      // set start/stop, calculate bin steps
      const double step = (stop - start) / num;
 
      // instantiate vector to hold bins
      std::vector<double> bins;

      // and fill vector
      double edge = start;
      for (std::size_t inum = 0; inum < num; ++inum) {
        bins.push_back( edge );
        edge += step;
      }
      bins.push_back( edge );
      return bins;

    }  // end 'GetBinEdges(uint32_t, double, double)'



    // ------------------------------------------------------------------------
    //! Helper method to divide a range into a certain number of log bins
    // ------------------------------------------------------------------------
    std::vector<double> GetBinEdgesLog(
      const uint32_t num,
      const double start,
      const double stop,
      const double base = TMath::E()
    ) { 

      // throw error if start/stop are out of order
      // or if num is zero
      if (num <= 0)     assert(num > 0);
      if (start > stop) assert(start <= stop);

      // divide range in log space
      std::vector<double> bins = GetBinEdges(num, Log(start), Log(stop));

      // transform back from log & return
      std::transform(
        bins.begin(),
        bins.end(),
        bins.begin(),
        [&base](const double arg) {
          return Exponentiate(arg, base);
        }
      ); 
      return bins;

    }  // end 'GetBinEdgesLog(uint32_t, double, double, double)'

  }  // end Tools namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
