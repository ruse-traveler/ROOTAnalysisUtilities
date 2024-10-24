/// ============================================================================
/*! \file    HistIndex.hxx
 *  \authors Derek Anderson
 *  \date    10.24.2024
 *
 *  Base class for a histogram index.
 */
/// ============================================================================

#ifndef RAU_HISTINDEX_HXX
#define RAU_HISTINDEX_HXX

// c++ utilities
#include <array>
#include <string>



namespace ROOTAnalysisUtilities {
  namespace Hist {

    // ========================================================================
    //! Histogram Index
    // ========================================================================
    /*! Base class for a "histogram index", a collection
     *  of indices of various bins.
     *
     *  TODO the idea here is that specializations somehow provide
     *  rules that tell you how to
     *    (1) get a list of indices, given a group of arguments; and
     *    (2) get a string representation of these indices.
     *
     *  TODO Some thoughts:
     *    - Maybe make size of index list a template...
     *    - Then have a couple of members of type std::function
     *      for the above rules?
     */ 
    template <std::size_t N> class Index {

      private:

        std::array<std::size_t, N> m_values;

      protected:

        /* TODO other inheritable methods go here */

      public:

        // FIXME maybe THIS is the thing the user overrides?
        virtual std::string Hash() = 0;

        Index()  {};
        ~Index() {};

    };

  }  // end Hist namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================

