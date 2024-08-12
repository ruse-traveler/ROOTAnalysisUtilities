/// ---------------------------------------------------------------------------
/*! \file   RBinsDef.hxx
 *  \author Derek Anderson
 *  \date   08.12.2024
 *
 *  Consolidates binning definition
 */
/// ---------------------------------------------------------------------------

#ifndef RBinsDef_hxx
#define RBinsDef_hxx

// c++ utilities
#include <vector>



namespace RGraphicalUtilities {
  namespace Elements {

    // ------------------------------------------------------------------------
    //! Binning definition
    // ------------------------------------------------------------------------
    struct RBinsDef {

      // flags
      bool isVariable = false;

      // for uniform binning
      size_t nbins = 1;
      double start = 0.;
      double stop  = 1.;

      // for variable binning
      std::vector<double> bins;

      // set uniform binning
      void SetBins(const size_t num, const double begin, const double end) {
        nbins      = num;
        start      = begin;
        stop       = end;
        isVariable = false;
        return;
      }  // end 'SetBins(size_t, double, double)'

      // set variable binning
      void SetVariableBins(const std::vector<double> vecBins) {
        bins       = vecBins;
        nbins      = vecBins.size() + 1;
        isVariable = true;
        return;
      }  // end 'SetVariableBins(size_t, vector<double>)'

      // reset data members
      void Reset() {
        nBins = 1;
        start = 0;
        stop  = 1;
        bins.clear();
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      RBinsDef()  {};
      ~RBinsDef() {};

      // ctor accepting arguments
      RBinsDef(const size_t num, const double begin, const double end) {
        SetStyle(num, begin, end);
      }
      RBinsDef(const std::vector<double> vecBins) {
        SetStyle(vecBins);
      }

    };  // end RBinsDef

  }  // end Elements namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
