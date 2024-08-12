/// ---------------------------------------------------------------------------
/*! \file   RGraphicalUtilities.hxx
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

// components
#include "Attributes/Attributes.hxx"
#include "Elements/Elements.hxx"
#include "Objects/Objects.hxx"

// alias for convenience
using RGU = RGraphicalUtilities;



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

}  // end RGraphicalUtitlities namespace

#endif

//end -------------------------------------------------------------------------
