// ----------------------------------------------------------------------------
// 'TGraphicalHelper.hh'
// Derek Anderson
// 09.23.2023
//
// Namespace to consolidate various objects & methods
// useful for interacting with graphical objects in
// ROOT.
// ----------------------------------------------------------------------------

#include <string>


namespace TGraphicalHelper {

  // enums --------------------------------------------------------------------

  enum Axis {
    x,
    y,
    z
  };

  enum Class {
    TH1,
    TH2,
    TH3,
    TF1,
    TF2,
    TGraph,
    TGraph2D
  };

  // types --------------------------------------------------------------------

  struct TMarkerStyle {
    uint16_t color = 1;
    uint16_t style = 1;
    float    alpha = 0.;
    float    size  = 1.;

    void SetStyle(const uint16_t col, const uint16_t sty, const float alp, const float siz) {
      color = col;
      style = sty;
      alpha = alp;
      size  = siz;
      return;
    }  // end 'SetStyle(uint16_t, uint16_t, float, float)'

    void Reset() {
      color = 1;
      style = 1;
      alpha = 0.;
      size  = 1.;
      return;
    }  // end 'Reset()' 
  };  // end TMarkerStyle def



  struct TLineStyle {
    uint16_t color = 1;
    uint16_t style = 1;
    uint16_t width = 1;
    float    alpha = 0.;

    void SetStyle(const uint16_t col, const uint16_t sty, const uint16_t wid, const float alp) {
      color = col;
      style = sty;
      width = wid;
      alpha = alp;
      return;
    }  // end 'SetStyle(uint16_t, uint16_t, uint16_t, float)'

    void Reset() {
      color = 1;
      style = 1;
      width = 1;
      alpha = 0.;
      return;
    }  // end 'Reset()'
  };  // end TLineStyle def



  struct TFillStyle {
    uint16_t color = 1;
    uint16_t style = 1;
    float    alpha = 0.;

    void SetStyle(const uint16_t col, const uint16_t sty, const float alp) {
      color = col;
      style = sty;
      alpha = alp;
      return;
    }

    void Reset() {
      color = 1;
      style = 1;
      alpha = 0.;
      return;
    }  // end 'Reset()'
  };  // end TFillStyle def



  struct TTitleStyle {
    uint16_t color  = 1;
    uint16_t center = 0;
    uint16_t font   = 42;
    float    size   = 0.04;
    float    alpha  = 0.;
    float    offset = 1.1;
    string   title  = "";

    void SetStyle(const uint16_t col, const uint16_t cen, const uint16_t fon, const float siz, const float alp, const float off, const string ttl) {
      color  = col;
      center = cen;
      font   = fon;
      size   = siz;
      alpha  = alp;
      offset = off;
      title  = ttl;
      return;
    }  // end 'SetStyle(uint16_t, uint16_t, uint16_t, float, float, float, string)'

    void Reset() {
      color  = 1;
      center = 0;
      font   = 42;
      size   = 0.04;
      alpha  = 0.;
      offset = 1.1;
      title  = "";
      return;
    }  // end 'Reset()'
  };  // end TTitleStyle def



  struct TLabelStyle {
    uint16_t color  = 1;
    uint16_t font   = 42;
    float    size   = 0.04;
    float    alpha  = 0.;
    float    offset = 0.005;

    void SetStyle(const uint16_t col, const uint16_t fon, const float siz, const float alp, const float off) {
      color  = col;
      font   = fon;
      size   = siz;
      alpha  = alp;
      offset = off;
      return;
    }  // end 'SetStyle(uint16_t, uint16_t, float, float, float)'

    void Rest() {
      color  = 1;
      font   = 42;
      size   = 0.04;
      alpha  = 0.;
      offset = 0.005;
      return;
    }  // end 'Reset()'
  };  // end TLabelStyle def



  struct TAxisStyle {
    TTitleStyle title;
    TLabelStyle label;

    void SetStyle(const TTitleStyle ttl, const TLabelStyle lab) {
      title = ttl;
      label = lab;
      return;
    }  // 'SetStyle(TTitleStyle, TLabelStyle)'

    void Reset() {
      title.Reset();
      label.Reset();
      return;
    }  // end 'Reset()'
  };  // end TAxisStyle

//end -------------------------------------------------------------------------
