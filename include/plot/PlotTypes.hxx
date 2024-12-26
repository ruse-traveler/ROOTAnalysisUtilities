/// ===========================================================================
/*! \file   PlotTypes.hxx
 *  \author Derek Anderson
 *  \date   10.26.2024
 *
 *  Useful tools related to plotting.
 */
/// ===========================================================================

#ifndef RAU_PLOTTYPES_HXX
#define RAU_PLOTTYPES_HXX

// c++ utilities
#include <array>
#include <map>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TObject.h>



namespace ROOTAnalysisUtilities {
  namespace Types {

    // ------------------------------------------------------------------------
    //! Convenient plotting types
    // ------------------------------------------------------------------------
    typedef std::array<float, 4>               Vertices;
    typedef std::array<float, 4>               Margins;
    typedef std::vector<TObject*>              Objects;
    typedef std::vector<std::string>           TextList;
    typedef std::vector<std::string>           LabelList;
    typedef std::pair<float, float>            Interval;
    typedef std::pair<uint32_t, uint32_t>      Dimensions;
    typedef std::map<std::string, std::size_t> LabelToIndexMap;



    // ------------------------------------------------------------------------
    //! Different margins of a pad or canvas
    // ------------------------------------------------------------------------
    enum Margin {Top, Right, Bottom, Left};

  }  // end Types namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
