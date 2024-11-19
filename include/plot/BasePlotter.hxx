/// ===========================================================================
/*! \file   BasePlotter.hxx
 *  \author Derek Anderson
 *  \date   11.19.2024
 *
 *  A base class to consolidate plotting routines
 */
/// ===========================================================================

#ifndef BasePlotter_hxx
#define BasePlotter_hxx

// c++ utilities
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include <optional>
#include <iostream>
// root libraries
#include <TH2.h>
#include <TFile.h>
#include <TGraph.h>
#include <TObject.h>
#include <TGraphErrors.h>
// analysis utilities
#include "../../utility/PlotHelper.hxx"
#include "../../utility/HistHelper.hxx"

// abbreviate common namespaces
namespace PH = PlotHelper;
namespace HH = HistHelper;

// useful alias
typedef std::vector<PH::Style> Styles; 



// ============================================================================
//! Base plotter input
// ============================================================================
/*! A small struct to consolidate input for
 *  plotting routines
 */
struct PlotterInput {

  std::string     file;    // file where object is
  std::string     object;  // object to be plotted
  std::string     rename;  // rename object to this
  std::string     legend;  // legend entry
  PH::Style::Plot style;   // marker, line, and fill style

};  // end PlotterInput



// ============================================================================
//! Base plotter 
// ============================================================================
/*! This class conslidates plotting routines
 */
class BasePlotter {

  public:

    // default ctor/dtor
    BasePlotter();
    ~BasePlotter();

    // ctor accepting arguments
    BasePlotter(const PH::Style& plot, const PH::Style& text, std::optional<PH::TextBox> box);

    // getters
    PH::Style   GetBasePlotStyle() const {return m_basePlotStyle;}
    PH::Style   GetBaseTextStyle() const {return m_baseTextStyle;}
    PH::TextBox GetTextBox()       const {return m_textBox;}

    // setters
    void SetBasePlotStyle(const PH::Style& style) {m_basePlotStyle = style;}
    void SetBaseTextStyle(const PH::Style& style) {m_baseTextStyle = style;}
    void SetTextBox(const PH::TextBox& text)      {m_textBox       = text;}

    // plotting routines
    void DoResolutionLinearityComparison(const std::vector<PlotterInput>& inputs, const PH::PlotRange& plotrange, const PH::Canvas& candef, const HH::Definition& framedef, TFile* ofile);

    // static methods
    static TFile*   OpenFile(const std::string& name, const std::string &option);
    static TObject* GrabObject(const std::string& object, TFile* file);

  private:

    // members
    PH::Style   m_basePlotStyle;
    PH::Style   m_baseTextStyle;
    PH::TextBox m_textBox;

    // helper methods
    Styles GenerateStyles(const std::vector<PlotterInput>& inputs);

};  // end BasePlotter

#endif

// end ========================================================================
