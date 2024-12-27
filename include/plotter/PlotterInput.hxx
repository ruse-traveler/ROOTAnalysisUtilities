/// ===========================================================================
/*! \file   PlotterInput.hxx
 *  \author Derek Anderson
 *  \date   12.27.2024
 *
 *  Definition of the input for a plotting routine.
 */
/// ===========================================================================

#ifndef RAU_PLOTTERINPUT_HXX
#define RAU_PLOTTERINPUT_HXX

// c++ utilities
#include <string>
// rau components
#include "../plot/PlotStyle.hxx"



namespace ROOTAnalysisUtilities {
  namespace Plotter {

    // ========================================================================
    //! Plotter input
    // ========================================================================
    /*! A small struct to consolidate input for
     *  plotting routines
     */
    struct Input {

      std::string       file;    ///!< file where object is
      std::string       object;  ///!< object to be plotted
      std::string       rename;  ///!< rename object to this
      std::string       legend;  ///!< legend entry
      Plot::Style::Plot style;   ///!< marker, line, and fill style

    };  // end Input

  }  // end Plotter namespace
}    // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
