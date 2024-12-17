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
  //! Text box definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define a TPaveText
   */
  class TextBox {

    private:

      // data members
      TextList    m_text;
      Vertices    m_vtxs;
      std::string m_opt = "NDC NB";

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      TextList    GetText()     const {return m_text;}
      Vertices    GetVertices() const {return m_vtxs;}
      std::string GetOption()   const {return m_opt;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetText(const TextList& text)     {m_text = text;}
      void SetVertices(const Vertices& vtxs) {m_vtxs = vtxs;}
      void SetOption(const std::string& opt) {m_opt  = opt;}

      // ----------------------------------------------------------------------
      //! Add a line of text
      // ----------------------------------------------------------------------
      void AddText(const std::string& line) {

        m_text.push_back( line );
	return;

      }  // end 'AddText(std::string&)'

      // ----------------------------------------------------------------------
      //! Create a TPaveText*
      // ----------------------------------------------------------------------
      TPaveText* MakeTPaveText() {

        TPaveText* pt = new TPaveText( m_vtxs[0], m_vtxs[1], m_vtxs[2], m_vtxs[3], m_opt.data() );
        for (const std::string& text : m_text) {
          pt -> AddText( text.data() );
        }
        return pt;

      }  // end 'MakeTPaveText()'
 
      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      TextBox()  {};
      ~TextBox() {};

      // ----------------------------------------------------------------------
      //! ctor accepting arguments
      // ----------------------------------------------------------------------
      TextBox(
        const TextList& text, 
	const Vertices& vtxs,
        const std::string& opt = "NDC NB"
      ) {

        m_text = text;
        m_vtxs = vtxs;
        m_opt  = opt;

      }  // end ctor(TextList&, Vertices&, std::string&)'

  };  // end TextBox




  // ==========================================================================
  //! General options for pads/canvases
  // ==========================================================================
  /*! A small struct to consolidate options
   *  common to both TPads & TCanvases
   */  
  struct PadOpts {

    // members
    uint32_t logx  = 0;
    uint32_t logy  = 0;
    uint32_t tickx = 1;
    uint32_t ticky = 1;
    uint32_t gridx = 0;
    uint32_t gridy = 0;
    uint32_t bmode = 0;
    uint32_t bsize = 2;
    uint32_t frame = 0;

    // ------------------------------------------------------------------------
    //! Apply options to a TPad or TCanvas
    // ------------------------------------------------------------------------
    template <typename T> void Apply(T* pad) const {

      pad -> SetLogx(logx);
      pad -> SetLogy(logy);
      pad -> SetTicks(tickx, ticky);
      pad -> SetGrid(gridx, gridy);
      pad -> SetBorderMode(bmode);
      pad -> SetBorderSize(bsize);
      pad -> SetFrameBorderMode(frame);
      return;

    }  // end 'Apply(T*)'

    // ------------------------------------------------------------------------
    //! default ctor/dtor
    // ------------------------------------------------------------------------
    PadOpts()  {};
    ~PadOpts() {};

    // ------------------------------------------------------------------------
    //! ctor accepting only log values
    // ------------------------------------------------------------------------
    PadOpts(const std::pair<uint32_t, uint32_t> log) {

      logx = log.first;
      logy = log.second;

    }  // end ctor(std::pair<uint32_t, uint32_t>)'

    // ------------------------------------------------------------------------
    //! ctor accepting all arguments
    // ------------------------------------------------------------------------
    PadOpts(
      const std::pair<uint32_t, uint32_t> log,
      const std::pair<uint32_t, uint32_t> tick,
      const std::pair<uint32_t, uint32_t> grid,
      const uint32_t mode = 0,
      const uint32_t size = 2,
      const uint32_t framearg = 0
    ) {

      logx  = log.first;
      logy  = log.second;
      tickx = tick.first;
      ticky = tick.second;
      gridx = grid.first;
      gridy = grid.second;
      bmode = mode;
      bsize = size;
      frame = framearg;

    }  // end ctor(std::pair<uint32_t, uint32_t> x 3, uint32_t x 3)'

  };  // end Options



  // ==========================================================================
  //! Pad definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define and work with a TPad 
   */  
  class Pad {

    private:

      // members
      PadOpts     m_opts;
      Vertices    m_vtxs;
      Margins     m_mgns;
      std::string m_name;
      std::string m_title = "";

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      PadOpts     GetOptions()  const {return m_opts;}
      Vertices    GetVertices() const {return m_vtxs;}
      Margins     GetMargins()  const {return m_mgns;}
      std::string GetName()     const {return m_name;}
      std::string GetTitle()    const {return m_title;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetOptions(const PadOpts& opts)   {m_opts  = opts;}
      void SetVertices(const Vertices& vtxs) {m_vtxs  = vtxs;}
      void SetMargins(const Margins& mgns)   {m_mgns  = mgns;}
      void SetName(const std::string& name)  {m_name  = name;}
      void SetTitle(const std::string& ttl)  {m_title = ttl;}

      // ----------------------------------------------------------------------
      //! Create a TPad 
      // ----------------------------------------------------------------------
      TPad* MakeTPad() const {

        // create pad
        TPad* pad = new TPad(
          m_name.data(),
          m_title.data(),
          m_vtxs[0],
          m_vtxs[1],
          m_vtxs[2],
          m_vtxs[3]
        );

        // set margins
        pad -> SetTopMargin( m_mgns[Margin::Top] );
        pad -> SetRightMargin( m_mgns[Margin::Right] );
        pad -> SetBottomMargin( m_mgns[Margin::Bottom] );
        pad -> SetLeftMargin( m_mgns[Margin::Left] );

        // apply options and return pointer
	m_opts.Apply(pad);
        return pad;

      }  // end 'MakeTPad()'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Pad()  {};
      ~Pad() {};

      // ----------------------------------------------------------------------
      //! ctor accepting all members
      // ----------------------------------------------------------------------
      Pad(
        const std::string& name,
        const std::string& title,
        const Vertices& vtxs,
        const Margins& mgns,
        const PadOpts& opts
      ) {

        m_name  = name;
        m_title = title;
        m_vtxs  = vtxs;
        m_mgns  = mgns;
        m_opts  = opts;

      }  // end ctor(std::string& x 2, Vertices&, Margins&, PadOpts&)'

  };  // end Pad



  // ==========================================================================
  //! Canvas definition
  // ==========================================================================
  /*! A small class to consolidate necessary data
   *  to define and work with a TCanvas.
   */ 
  class Canvas {

    private:

      // members
      PadOpts          m_opts;
      Margins          m_mgns;
      Dimensions       m_dims;
      std::string      m_name;
      std::string      m_title = "";
      std::vector<Pad> m_pads;

    public:

      // ----------------------------------------------------------------------
      //! Getters
      // ----------------------------------------------------------------------
      PadOpts          GetOptions()    const {return m_opts;}
      Margins          GetMargins()    const {return m_mgns;}
      Dimensions       GetDimensions() const {return m_dims;}
      std::string      GetName()       const {return m_name;}
      std::string      GetTitle()      const {return m_title;}
      std::vector<Pad> GetPads()       const {return m_pads;}

      // ----------------------------------------------------------------------
      //! Setters
      // ----------------------------------------------------------------------
      void SetOptions(const PadOpts& opts)       {m_opts  = opts;}
      void SetMargins(const Margins& mgns)       {m_mgns  = mgns;}
      void SetDimensions(const Dimensions& dims) {m_dims  = dims;}
      void SetName(const std::string& name)      {m_name  = name;}
      void SetTitle(const std::string& ttl)      {m_title = ttl;}
      void SetPads(const std::vector<Pad>& pads) {m_pads  = pads;}

      // ----------------------------------------------------------------------
      //! Add an associated pad
      // ----------------------------------------------------------------------
      void AddPad(const Pad& pad) {

        m_pads.push_back( pad );
        return;

      }  // end 'AddPad(Pad&)'

      // ----------------------------------------------------------------------
      //! Get a apecific associated pad
      // ----------------------------------------------------------------------
      Pad GetPad(const std::size_t index) {

        return m_pads.at(index);

      }  // end 'GetPad(std::size_t)'

      // ----------------------------------------------------------------------
      //! Create a TCanvas
      // ----------------------------------------------------------------------
      TCanvas* MakeTCanvas() const {

        // create canvas
        TCanvas* canvas = new TCanvas(
          m_name.data(),
          m_title.data(),
          m_dims.first,
          m_dims.second
        );

        // set margins if needed
        if (m_pads.empty()) {
          canvas -> SetTopMargin( m_mgns[Margin::Top] );
          canvas -> SetRightMargin( m_mgns[Margin::Right] );
          canvas -> SetBottomMargin( m_mgns[Margin::Bottom] );
          canvas -> SetLeftMargin( m_mgns[Margin::Left] );
        }

        // apply options and return pointer
	m_opts.Apply(canvas);
        return canvas;

      }  // end 'MakeTCanvas()'

      // ----------------------------------------------------------------------
      //! Create associated TPads
      // ----------------------------------------------------------------------
      std::vector<TPad*> MakeTPads() {

        std::vector<TPad*> pads;
        for (const auto& pad : m_pads) {
          pads.push_back( pad.MakeTPad() ); 
        }
        return pads;

      }  // end 'MakeTPads()'

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Canvas()  {};
      ~Canvas() {};

      // ----------------------------------------------------------------------
      //! ctor accepting all members
      // ----------------------------------------------------------------------
      Canvas(
        const std::string& name,
        const std::string& title,
        const Dimensions& dims,
        const PadOpts& opts,
        std::optional<Margins> mgns = std::nullopt,
        std::optional<std::vector<Pad>> pads = std::nullopt
      ) {

        // set necessary arguments
        m_name  = name;
        m_title = title;
        m_dims  = dims;
        m_opts  = opts;

        // set optional arguments
        if (mgns.has_value()) m_mgns = mgns.value();
        if (pads.has_value()) m_pads = pads.value();

      }  // end ctor(std::string& x 2, Dimensions&, PadOpts&, std::optional x 2)'

  };  // end Canvas



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
