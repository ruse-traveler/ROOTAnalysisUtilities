/// ===========================================================================
/*! \file   HistBinning.hxx
 *  \author Derek Anderson
 *  \date   10.24.2024
 *
 *  Definition of a histogram binning.
 */
/// ===========================================================================

#ifndef RAU_HISTBINNING_HXX
#define RAU_HISTBINNING_HXX

// c++ utilities
#include <vector>
// rau components
#include "HistTools.hxx"



namespace ROOTAnalysisUtilities {
  namespace Hist {

    // ==========================================================================
    //! Binning definition
    // ==========================================================================
    /*! A small class to consolidate data
     *  for defining histogram bins.
     */ 
    class Binning {

      private:

        // data members
        double              m_start;
        double              m_stop;
        uint32_t            m_num;
        std::vector<double> m_bins;

      public:

        // ----------------------------------------------------------------------
        //! Uniform bin getters
        //-----------------------------------------------------------------------
        uint32_t GetNum()   const {return m_num;}
        double   GetStart() const {return m_start;}
        double   GetStop()  const {return m_stop;}

        // ----------------------------------------------------------------------
        //! Variable bin getter
        // ----------------------------------------------------------------------
        std::vector<double> GetBins() const {return m_bins;}

        // ----------------------------------------------------------------------
        //! default ctor/dtor
        // ----------------------------------------------------------------------
        Binning()  {};
        ~Binning() {};

        // ----------------------------------------------------------------------
        //! ctor accepting uniform parameters
        // ----------------------------------------------------------------------
        Binning(const uint32_t num, const double start, const double stop) {

          m_num   = num;
          m_start = start;
          m_stop  = stop;
          m_bins  = Tools::GetBinEdges(m_num, m_start, m_stop);

        }  // end ctor(uint32_t, double, double)

        // ----------------------------------------------------------------------
        //! ctor accepting non-uniform parameters
        // ----------------------------------------------------------------------
        Binning(const std::vector<double> edges) {

          m_bins  = edges;
          m_num   = edges.size() - 1;
          m_start = edges.front();
          m_stop  = edges.back();

        }  // end ctor(std::vector<double>)

    };  // end Binning


  }  // end Hist namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
