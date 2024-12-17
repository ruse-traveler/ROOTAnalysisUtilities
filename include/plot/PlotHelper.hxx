/// ===========================================================================
/*! \file   PlotHelper.hxx
 *  \author Derek Anderson
 *  \date   10.11.2024
 *
 *  A lightweight namespace to help plot things in ROOT.
 */
/// ===========================================================================

#ifndef PlotHelper_hxx
#define PlotHelper_hxx

// c++ utilities
#include <map>
#include <array>
#include <string>
#include <vector>
#include <utility>
#include <optional>
#include <iostream>
#include <algorithm>
// root libraries
#include <TF2.h>
#include <TF3.h>
#include <TH2.h>
#include <TH3.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TPaveText.h>
#include <TGraphErrors.h>
#include <TGraph2DErrors.h>
#include <TGraphAsymmErrors.h>



// ============================================================================
//! Plot Helper
// ============================================================================
/*! A small namespace to help plot things
 *  in ROOT.
 */
namespace PlotHelper {

  // ==========================================================================
  //! Plot (pad/canvas) manager
  // ==========================================================================
  /*! A small class to hold/organize the pointers
   *  to a TCanvas and all of its associated pads.
   */ 
  class PlotManager {

    private:

      // canvas definition
      Canvas m_define;

      // root members
      TCanvas*           m_canvas;
      std::vector<TPad*> m_pads;

      // pad-label-to-index map
      LabelList       m_labels;
      LabelToIndexMap m_labtoindex;

      // ----------------------------------------------------------------------
      //! Make a pad label
      // ----------------------------------------------------------------------
      std::string MakePadLabel(const std::size_t index) const {

        // by default use the index as a label
        std::string label = std::to_string(index);

        // but if corresponding label exists, use that
        if (index < m_labels.size()) {
          label = m_labels[index];
        }
        return label;

      }  // end 'MakePadLabel(std::size_t)'

      // ----------------------------------------------------------------------
      //! Make label-to-index map
      // ----------------------------------------------------------------------
      void MakeLabelToIndexMap() {

        // emit warning if size of label list and pad vector
        // are different
        if (m_labels.size() != m_define.GetPads().size()) {
          std::cerr << "WARNING: provided label list is NOT the same length as the list of pads to make!" << std::endl;
        }

        // create label-to-index map
        for (std::size_t ipad = 0; ipad < m_define.GetPads().size(); ++ipad) {
          const std::string label = MakePadLabel(ipad);
          m_labtoindex[label] = ipad;
        }
        return;

      }  // end 'MakeLabelToIndexMap()'

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      Canvas             GetDefinition() const {return m_define;}
      TCanvas*           GetTCanvas()    const {return m_canvas;}
      LabelList          GetPadLabels()  const {return m_labels;}
      std::vector<TPad*> GetTPads()      const {return m_pads;}

      // ----------------------------------------------------------------------
      //! Setters 
      // ----------------------------------------------------------------------
      void SetDefinition(const Canvas& define)   {m_define = define;}
      void SetPadLabels(const LabelList& labels) {m_labels = labels;}

      // ----------------------------------------------------------------------
      //! Make canvas and pads 
      // ----------------------------------------------------------------------
      void MakePlot() {

        // create canvas/pads
        m_canvas = m_define.MakeTCanvas();
        m_pads   = m_define.MakeTPads();

        // generate lable-index map & exit
        MakeLabelToIndexMap();
        return;

      }  // end 'MakePlot()' '

      // ----------------------------------------------------------------------
      //! Draw canvas and pads
      // ----------------------------------------------------------------------
      void Draw() {

        m_canvas -> Draw();
        for (TPad* pad : m_pads) {
          pad -> Draw();
        }
        return;

      }  // end 'Draw()'

      // ----------------------------------------------------------------------
      //! Write canvas
      // ----------------------------------------------------------------------
      void Write() {

        m_canvas -> Write();
        return;

      }  // end 'Write()'

      // ----------------------------------------------------------------------
      //! Close canvas
      // ----------------------------------------------------------------------
      void Close() {

        m_canvas -> Close();
        return;

      }  // end 'Close()'

      // ----------------------------------------------------------------------
      //! Get a specific pad via its label
      // ----------------------------------------------------------------------
      TPad* GetTPad(const std::string& label) const {

        return m_pads.at( m_labtoindex.at(label) );

      }  // end 'GetTPad(std::string&)'

      // ----------------------------------------------------------------------
      //! Get a specific pad via its index
      // ----------------------------------------------------------------------
      TPad* GetTPad(const std::size_t index) const {

        return m_pads.at(index);

      }  // end 'GetTPad(std::size_t)'

      // ----------------------------------------------------------------------
      //! default ctor/dtor 
      // ----------------------------------------------------------------------
      PlotManager()  {};
      ~PlotManager() {};

      // ----------------------------------------------------------------------
      //! ctor accepting a canvas definition and possibly a list of pad labels
      // ----------------------------------------------------------------------
      PlotManager(const Canvas& define, std::optional<LabelList> padlabels = std::nullopt) {

        m_define = define;
        if (padlabels.has_value()) {
          m_labels = padlabels.value();
        }

      }   // end ctor(Canvas&)' 

  };  // end PlotManager

}  // end PlotHelper namespace

#endif

// end ========================================================================
