/// ===========================================================================
/*! \file   HistBins.hxx
 *  \author Derek Anderson
 *  \date   10.24.2024
 *
 *  Abstract base class for a bin database.
 */
/// ===========================================================================

#ifndef RAU_HISTBINS_HXX
#define RAU_HISTBINS_HXX

// c++ utilities
#include <cassert>
#include <map>
#include <string>
// rau components
#include "HistBinning.hxx"



namespace ROOTAnalysisUtilities {
  namespace Hist {

    // ========================================================================
    //! Bin Database
    // ========================================================================
    /*! Base class for a "bin database", a way to centralize
     *  binning for various quantities. Methods are provided
     *  to update existing bins or add new bin definitions
     *  on the fly.
     */
    class Bins {

      private:

        std::map<std::string, Binning> m_bins;

      protected:

        // --------------------------------------------------------------------
        //! Initialize bin map
        // --------------------------------------------------------------------
        /*! Virtual method called by ctor to initialize
         *  the bin map.
         */
        void InitBins(); 

      public:

        // --------------------------------------------------------------------
        //! Add a binning
        // --------------------------------------------------------------------
        void Add(const std::string& name, const Binning& binning) {

          // throw error if binning already exists
          if (m_bins.count(name) >= 1) {
            assert(m_bins.count(name) == 0);
          }

          // otherwise insert new binning
          m_bins.insert( {name, binning} );
          return;

        }  // end 'Add(std::string&, Binning&)'

        // --------------------------------------------------------------------
        //! Change a binning
        // --------------------------------------------------------------------
        void Set(const std::string& variable, const Binning& binning) {

          // throw error if binning doesn't exist
          if (m_bins.count(variable) == 0) {
            assert(m_bins.count(variable) >= 1);
          }

          // otherwise update binning
          m_bins[variable] = binning;
          return;

        }  // end 'Set(std::string&, Binning&)'

        // --------------------------------------------------------------------
        //! Get a binning
        // --------------------------------------------------------------------
        Binning Get(const std::string& variable) {

          // throw error if binning doesn't exist
          if (m_bins.count(variable) == 0) {
            assert(m_bins.count(variable) == 0);
          }

          // otherwise return binning
          return m_bins.at(variable);

        }  // end 'Get(std::string&)'

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Bins()  { InitBins(); };
        ~Bins() {};

    };  // end Bins

  }  // end Hist namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
