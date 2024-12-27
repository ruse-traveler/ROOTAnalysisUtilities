/// ===========================================================================
/*! \file   PlotterBase.hxx
 *  \author Derek Anderson
 *  \date   12.27.2024
 *
 *  A generic base class for "plotters", classes to consolidate
 *  various plotting routines.
 */
/// ===========================================================================

#ifndef RAU_PLOTTERBASE_HXX
#define RAU_PLOTTERBASE_HXX

// c++ utilities
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
#include <TObject.h>
#include <TPaveText.h>
// rau components
#include "../plot/Plot.hxx"
#include "PlotterInput.hxx"
#include "PlotterTools.hxx"

// useful alias
typedef std::vector<ROOTAnalysisUtilities::Plotter::Input> Inputs;
typedef std::vector<ROOTAnalysisUtilities::Plot::Style> Styles; 



namespace ROOTAnalysisUtilities {
  namespace Plotter {

    // ========================================================================
    //! Base plotter 
    // ========================================================================
    /*! A generic, base class for various classes to consolidate
     *  various plotting routines. 
     */
    class Base {

      protected:

        // members
        Plot::Style   m_basePlotStyle;
        Plot::Style   m_baseTextStyle;
        Plot::TextBox m_textBox;

        // --------------------------------------------------------------------
        //! Generate list of styles to be applied
        // --------------------------------------------------------------------
        Styles GenerateStyles(const Inputs& inputs) const {

          Styles styles( inputs.size(), m_basePlotStyle );
          for (std::size_t isty = 0; isty < inputs.size(); ++isty) {
            styles[isty].SetPlotStyle( inputs[isty].style );
          }
          return styles;

        }  // end 'GenerateStyles(std::size_t)'

      public:

        // --------------------------------------------------------------------
        //! Getters
        // --------------------------------------------------------------------
        Plot::Style   GetBasePlotStyle() const {return m_basePlotStyle;}
        Plot::Style   GetBaseTextStyle() const {return m_baseTextStyle;}
        Plot::TextBox GetTextBox()       const {return m_textBox;}

        // --------------------------------------------------------------------
        //! Setters
        // --------------------------------------------------------------------
        void SetBasePlotStyle(const Plot::Style& style) {m_basePlotStyle = style;}
        void SetBaseTextStyle(const Plot::Style& style) {m_baseTextStyle = style;}
        void SetTextBox(const Plot::TextBox& text)      {m_textBox       = text;}

        /* TODO add
         *   - Compare spectra against a baseline
         *   - Compare ratios of pairs of spectra
         */ 

        // --------------------------------------------------------------------
        //! Plot various spectra
        // --------------------------------------------------------------------
        /*! Plots a variety of spectra from different sources. Can be
         *  overwritten. 
         *
         *  \param[in]  inputs list of objects to plot and their details
         *  \param[in]  range  (x, y) ranges to plot
         *  \param[in]  canvas definition of the canvas to draw on
         *  \param[out] ofile  file to write to
         *  \param[in]  header optionally, can provide header for legend
         */
        virtual void PlotSpectra(
          const Inputs& inputs,
          const Plot::Range& range,
          const Plot::Canvas& canvas,
          TFile* ofile,
          std::optional<std::string> header
        ) {

          // announce start
          std::cout << "\n -------------------------------- \n"
                    << "  Beginning energy spectra plotting!\n"
                    << "    Opening inputs:"
                    << std::endl;

          // open inputs
          std::vector<TFile*> ifiles;
          std::vector<TH1*>   ihists;
          for (const Input& input : inputs) {

            ifiles.push_back(
              Tools::OpenFile(input.file, "read")
            );
            ihists.push_back(
              (TH1*) Tools::GrabObject( input.object, ifiles.back() )
            );
            ihists.back() -> SetName( input.rename.data() );
            std::cout << "      File = " << input.file << "\n"
                      << "      Hist = " << input.object
                      << std::endl;

          }  // end input loop

          // determine no. of legend entries
          const std::size_t nlines = header.has_value() 
                                   ? ihists.size() + 1
                                   : ihists.size();

          // set legend dimensions
          const float           spacing   = m_baseTextStyle.GetTextStyle().spacing;
          const float           legheight = Tools::GetHeight(nlines, spacing);
          const Types::Vertices vtxleg    = {0.3, 0.1, 0.5, (float) 0.1 + legheight};

          // define legend
          Plot::Legend legdef;
          for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
            legdef.AddEntry( Plot::Legend::Entry(ihists[ihst], inputs[ihst].legend, "PF") );
          }
          legdef.SetVertices( vtxleg );
          if (header.has_value()) {
            legdef.SetHeader( header.value() );
          }

          // create root objects
          TLegend*   legend = legdef.MakeLegend();
          TPaveText* text   = m_textBox.MakeTPaveText();
          std::cout << "    Created legend and text box." << std::endl;

          // set hist styles
          Styles styles = GenerateStyles( inputs );
          for (std::size_t ihst = 0; ihst < ihists.size(); ++ihst) {
            styles[ihst].SetPlotStyle( inputs[ihst].style );
            styles[ihst].Apply( ihists[ihst] );
            ihists[ihst] -> GetXaxis() -> SetRangeUser( range.x.first, range.x.second );
            ihists[ihst] -> GetYaxis() -> SetRangeUser( range.y.first, range.y.second );

            // apply styles to fit functions
            for (auto function : *ihists[ihst] -> GetListOfFunctions()) {
              styles[ihst].Apply( (TF1*) function );
            }
          }

          // set legend/text styles
          m_baseTextStyle.Apply( legend );
          m_baseTextStyle.Apply( text );
          std::cout << "    Set styles." << std::endl;

          // draw plot
          Plot::Manager manager = Plot::Manager( canvas );
          manager.MakePlot();
          manager.Draw();
          manager.GetTCanvas() -> cd();
          ihists[0] -> Draw();
          for (std::size_t ihst = 1; ihst < ihists.size(); ++ihst) {
            ihists[ihst] -> Draw("same");
          }
          legend -> Draw();
          text   -> Draw();
          std:: cout << "    Made plot." << std::endl;

          // save output
          ofile -> cd();
          for (auto hist : ihists) {
            hist -> Write();
          }
          manager.Write();
          manager.Close();
          std::cout << "    Saved output." << std::endl;

          // close input files
          for (TFile* ifile : ifiles) {
            ifile -> cd();
            ifile -> Close();
          }
          std::cout << "    Closed input files." << std::endl;

          // announce end
          std::cout << "  Finished spectra plotting!\n"
                    << " -------------------------------- \n"
                    << endl;

          // exit routine
          return;

        }  // end 'PlotSpectra(Inputs&, Plot::Range&, Plot::Canvs&, TFile*, std::optional<std::string>)'

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Base()  {};
        ~Base() {};

        // --------------------------------------------------------------------
        //! ctor accepting arguments
        // --------------------------------------------------------------------
        Base(
          const Plot::Style& plot,
          const Plot::Style& text,
          std::optional<Plot::TextBox> box
        ) {

          m_basePlotStyle = plot;
          m_baseTextStyle = text;
          if (box.has_value()) {
            m_textBox = box.value();
          }

        }  // end ctor(Plot::Style&, Plot::Style&, std::optional<Plot::TextBox>)'

    };  // end BasePlotter

  }  // end Plotter namespace
}    // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
