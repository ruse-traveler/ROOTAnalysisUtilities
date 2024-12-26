/// ===========================================================================
/*! \file   PlotTools.hxx
 *  \author Derek Anderson
 *  \date   10.24.2024
 *
 *  Useful tools related to plotting.
 */
/// ===========================================================================

#ifndef RAU_PLOTTOOLS_HXX
#define RAU_PLOTTOOLS_HXX

// c++ utilities
#include <optional>



namespace ROOTAnalysisUtilities {
  namespace Tools {

    // ------------------------------------------------------------------------
    //! Helper method to calculate a height based on line spacing
    // ------------------------------------------------------------------------
    float GetHeight(
      const std::size_t nlines,
      const float spacing,
      std::optional<float> off = std::nullopt
    ) {

      float height = nlines * spacing;
      if (off.has_value()) {
        height += off.value();
      }
      return height;

    }  // end 'GetHeight(std::size_t float, std::optional<float>)'

  }  // end Tools namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
