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
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
// rau components
#include "HistDefinition.hxx"
#include "HistIndex.hxx"



namespace ROOTAnalysisUtilities {
  namespace Hist {

    // ------------------------------------------------------------------------
    //! Alias for map of histograms
    // ------------------------------------------------------------------------
    template <typename T> using HistMap = std::map<std::string, T>;

    // ------------------------------------------------------------------------
    // Alias for a collection/grid of histograms
    // ------------------------------------------------------------------------
    template <typename T, typename U> using HistGrid = std::map<T, HistMap<U>>;



    // ========================================================================
    //! Histogram Manager
    // ========================================================================
    /*! Base class for a "histogram manager", a way to manage
     *  large collections of repeated histograms (e.g. consider
     *  situations where you have to fill the same histogram
     *  but for multiple cuts).
     *
     *  The user needs to specify an index -- derived from RAU::
     *  Hist::Index, which defines all of the rules for turning
     *  specific variables into indices -- and a content -- a
     *  struct or class that will consolidate all of the
     *  information to be histogrammed.
     *
     *  Furthermore, when specializing this class for a use case,
     *  the user needs to:
     *    (1) define how to generate all of the possible indices;
     *    (2) define how to generate all of the possible
     *        histograms;
     *    (3) and define how to fill all histograms for a given
     *        index.
     */ 
    template <typename I, typename C> class Manager {

      private:

        // data members
        bool                    m_do_errors;
        std::vector<I>          m_indices;
        std::vector<Definition> m_defs_1d;
        std::vector<Definition> m_defs_2d;
        std::vector<Definition> m_defs_3d;
        HistGrid<I, TH1D*>      m_hists_1d;
        HistGrid<I, TH2D*>      m_hists_2d;
        HistGrid<I, TH3D*>      m_hists_3d;

      protected:

        // --------------------------------------------------------------------
        //! Create histogram name
        // --------------------------------------------------------------------
        /*! Joins a histogram name and the string
         *  representation of an index to make a
         *  histogram name. Can be overwritten.
         */
        virtual std::string CreateHistName(const std::string hist, const I& index) {

          return hist + "_" + index.Hash();

        }  // end 'CreateHistName(std::string, I&)'

        // --------------------------------------------------------------------
        //! Create histogram maps
        // --------------------------------------------------------------------
        /*! Creates the actual collection (grids) of histograms
         *  based on the indices defined by `m_indices` and
         *  the histograms defined by `m_defs_*`. Can be
         *  overwritten.
         */ 
        virtual void CreateHistCollections() {

          // turn on errors if needed
          TH1::SetDefaultSumw2( m_do_errors );
          TH2::SetDefaultSumw2( m_do_errors );
          TH3::SetDefaultSumw2( m_do_errors );

          // create histograms
          for (const auto& index : m_indices) {
            for (const auto def : m_defs_1d) {
              def.AppendToName( CreateHistName(def.GetName(), index) );
              m_hists_1d[index].push_back( def.MakeTH1() );
            }
            for (const auto def : m_defs_2d) {
              def.AppendToName( CreateHistName(def.GetName(), index) );
              m_hists_2d[index].push_back( def.MakeTH2() );
            }
            for (const auto def : m_defs_3d) {
              def.AppendToName( CreateHistName(def.GetName(), index) );
              m_hists_3d[index].push_back( def.MakeTH3() );
            }
          }
          return;

        }  // end 'CreateHistCollection()'

        // --------------------------------------------------------------------
        //! Create tags for bins
        // --------------------------------------------------------------------
        /*! Derived class must specify how to
         *  generate all indices.
         */
        virtual void CreateIndices() = 0;

      public:

        // --------------------------------------------------------------------
        //! Setters
        // --------------------------------------------------------------------
        void SetDoSumw2(const bool sumw2) {m_do_errors = sumw2;}

        // --------------------------------------------------------------------
        //! Getters
        // --------------------------------------------------------------------
        bool        GetDoSumw2()  const {return m_do_errors;}
        std::size_t GetNIndices() const {return m_indices.size();}
        std::size_t GetNHist1D()  const {return m_indices.size() * m_defs_1d.size();}
        std::size_t GetNHist2D()  const {return m_indices.size() * m_defs_2d.size();}
        std::size_t GetNHist3D()  const {return m_indices.size() * m_defs_3d.size();}

        // --------------------------------------------------------------------
        //! Save histograms to a file
        // --------------------------------------------------------------------
        void SaveHists(TFile* file) const {

          // throw error if cd fails
          const bool good_cd = file -> cd();
          if (!good_cd) {
            assert(good_cd);
          }

          // loop through histogram maps
          for (const auto row : m_hists_1d) {
            for (const auto hists : row) {
              hists.second -> Write();
            }
          }
          for (const auto row : m_hists_2d) {
            for (const auto hists : row) {
              hists.second -> Write();
            }
          }
          for (const auto row : m_hists_3d) {
            for (const auto hists : row) {
              hists.second -> Write();
            }
          }
          return;

        }  // end 'SaveHists(TFile*)'

        // --------------------------------------------------------------------
        //! Generate histograms
        // --------------------------------------------------------------------
        /*! Derived class must specify how to
         *  generate all possible histograms.
         */ 
        virtual void GenerateHists() = 0;

        // --------------------------------------------------------------------
        //! Fill histograms
        // --------------------------------------------------------------------
        /*! Derived class must specify how to
         *  fill a row of histograms given
         *  an index and content.
         */ 
        virtual void FillHists(I index, C content) = 0;

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Manager()  {} 
        ~Manager() {};

        // --------------------------------------------------------------------
        //! ctor accepting whether or not to do errors
        // --------------------------------------------------------------------
        Manager(const bool sumw2) {m_do_errors = sumw2;}

    };  // end Manager

  }  // end Hist namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
