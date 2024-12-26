/// ===========================================================================
/*! \file   PlotRange.hxx
 *  \author Derek Anderson
 *  \date   12.16.2024
 *
 *  Definition of a plotting range.
 */
/// ===========================================================================

#ifndef RAU_PLOTRANGE_HXX
#define RAU_PLOTRANGE_HXX

// c++ utilities
#include <optional>
// rau components
#include "PlotTools.hxx"



namespace ROOTAnalysisUtilities {
  namespace Plot {

    // ========================================================================
    //! Plot range
    // ========================================================================
    /*! This struct groups together the start/stop
     *  points for all 3 axes for convenience.
     */
    struct Range {

      // members
      Tools::Interval x;
      Tools::Interval y;
      Tools::Interval z;

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Range()  {};
      ~Range() {};

      // ----------------------------------------------------------------------
      //! ctor accepting only x range
      // ----------------------------------------------------------------------
      Range(const Tools::Interval& xrange) {
        x = xrange;
      }

      // ----------------------------------------------------------------------
      //! ctor accepting x, y, and possibly z range
      // ----------------------------------------------------------------------
      Range(
        const Tools::Interval& xrange,
        const Tools::Interval& yrange,
        std::optional<Tools::Interval> zrange = std::nullopt
      ) {
        x = xrange;
        y = yrange;
        if (zrange.has_value()) {
          z = zrange.value();
        }
      }

    };  // end Range

  }  // end Plot namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
