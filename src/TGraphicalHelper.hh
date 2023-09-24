// ----------------------------------------------------------------------------
// 'TGraphicalHelper.h'
// Derek Anderson
// 09.23.2023
//
// Namespace to consolidate various objects & methods
// useful for interacting with graphical objects in
// ROOT.
// ----------------------------------------------------------------------------

namespace TGraphicalHelper {

  // enums --------------------------------------------------------------------

  enum Axis {
    x,
    y,
    z
  };

  // types --------------------------------------------------------------------

  struct TGraphicalUtility::TMarkerStyle {
    UInt_t  marker_color = 1;
    UInt_t  marker_style = 1;
    Float_t marker_alpha = 0.;
    Float_t marker_size  = 1.;
  };

  struct TGraphicalUtility::TLineStyle {
    UInt_t  line_color = 1;
    UInt_t  line_style = 1;
    UInt_t  line_width = 1;
    Float_t line_alpha = 0.;
  };

  struct TGraphicalUtility::TFillStyle {
    UInt_t  fill_color = 1;
    UInt_t  fill_style = 1;
    Float_t fill_alpha = 0.;
  };

  struct TGraphicalUtility::TAxisStyle {
    UInt_t  title_center = 0;
    UInt_t  title_font   = 42;
    UInt_t  label_font   = 42;
    Float_t title_size   = 0.04;
    Float_t label_size   = 0.04;
    Float_t title_offset = 1.1;
    Float_t label_offset = 0.005;
    TString axis_title   = "";
  };

//end -------------------------------------------------------------------------
