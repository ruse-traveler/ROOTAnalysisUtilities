/// ---------------------------------------------------------------------------
/*! \file   RGraphicalUtitlities.hxx
 *  \author Derek Anderson
 *  \date   08.07.2024
 *
 *  A namespace to consolidate various objects & methods
 *  useful for interacting with graphical objects in
 *  ROOT.
 */
/// ---------------------------------------------------------------------------

#ifndef RGraphicalUtilities_hxx
#define RGraphicalUtilities_hxx

// c++ utilities
#include <map>
#include <string>
#include <cassert>

// attributes
#include "Attributes/Attributes.hxx"



// ----------------------------------------------------------------------------
//! RGraphicalUtilities
// ----------------------------------------------------------------------------
/*! A namespace to consolidate various interfaces
 *  useful for interacting with graphical objects
 *  in ROOT.
 */
namespace RGraphicalUtitlities {

  // typedefs -----------------------------------------------------------------

  typedef std::vector<string>     SVec;
  typedef std::pair<float, float> FPair;



  // constants ----------------------------------------------------------------

  namespace {
    const size_t _NMaxAxes  = 3;
  };



  // enums --------------------------------------------------------------------

  enum Axis {
    x,
    y,
    z
  };

  enum Class {
    TH1,
    TH2,
    TH3,
    TF1,
    TF2,
    TGraph,
    TGraph2D
  };



  // object definitions -------------------------------------------------------

  struct RAxisDef {
    size_t nbins = 1;
    double start = 0.;
    double stop  = 1.;

    // for variable binning
    std::vector<double> bins;

    void SetBins(const size_t num, const double begin, const double end) {
      nbins = num;
      start = begin;
      stop  = end;
      return;
    }  // end 'SetBins(size_t, double, double)'

    void SetVariableBins(const std::vector<double> vecBins) {
      bins  = vecBins;
      nbins = vecBins.size() + 1;
      return;
    }  // end 'SetVariableBins(size_t, vector<double>)'

    void Reset() {
      nBins = 1;
      start = 0;
      stop  = 1;
      bins.clear();
      return;
    }  // end 'Reset()'
  };  // end 'TAxisDef'



  struct RHNDef {
    string name  = "";
    string title = "";

    // axes
    std::array<TAxisDef, _NMaxAxes> axes;

    void SetNameAndTitle(const string nam, const string ttl) {
      name  = nam;
      title = ttl;
      return;
    }  // end 'SetNameAndTitle(string, string)'

    void SetAxis(const TGraphicalUtitlities::Axis axis, const TAxisDef def) {
      axes[axis] = def;
      return;
    }  // end 'SetAxis(TGraphicalUtitlities::Axis, TAxisDef)'

    void Reset() {
      name = "";
      title = "";
      for (auto axis : axes) {
        axis.Reset();
      }
    }  // end 'Reset()'
  };  // end 'THNDef'

}  // end RGraphicalUtitlities namespace

#endif

//end -------------------------------------------------------------------------
