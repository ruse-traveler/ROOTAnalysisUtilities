/// ============================================================================
/*! \file    HistManager.hxx
 *  \authors Derek Anderson
 *  \date    10.24.2024
 *
 *  Base class for a histogram manager.
 */
/// ============================================================================

#ifndef RAU_HISTMANAGER_HXX
#define RAU_HISTMANAGER_HXX

// c++ utilities
#include <map>
#include <string>
#include <vector>
// root libraries
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
// rau components
#include "HistIndex.hxx"



namespace ROOTAnalysisUtilities {
  namespace Hist {

    // ========================================================================
    //! Histogram Manager
    // ========================================================================
    /*! Base class for a "histogram manager", a way to
     *  manage large collections of repeated histograms
     *  (e.g. consider situations where you have to fill
     *  the same histogram but for multiple cuts).
     *
     *  TODO the idea here is that when you create a specialization, you
     *  give it an index. All of the rules for turning specific variables
     *  into indices, etc. are baked into the "Index" class...
     */ 
    template <typename I> class Manager {

      private:

        std::vector<std::string> m_index_tags;
        std::map<I, std::string> m_indices;

      protected:

        // --------------------------------------------------------------------
        //! Create tags for bins
        // --------------------------------------------------------------------
        virtual void CreateBinTags() {

      public:

        // --------------------------------------------------------------------
        //!
        // --------------------------------------------------------------------
        virtual void GenerateHists() = 0;

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Manager()  {} 
        ~Manager() {};

    };  // end Manager

  }  // end Hist namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
