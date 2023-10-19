// ----------------------------------------------------------------------------
// 'TGraphicalUtitlities.hh'
// Derek Anderson
// 09.23.2023
//
// Namespace to consolidate various objects & methods
// useful for interacting with graphical objects in
// ROOT.
// ----------------------------------------------------------------------------

#include <map>
#include <string>
#include <cassert>



namespace TGraphicalUtitlities {

  // typedefs -----------------------------------------------------------------

  typedef std::vector<string>     SVec;
  typedef std::pair<float, float> FPair;



  // constants ----------------------------------------------------------------

  namespace {
    const size_t _NMaxAxes  = 3;
  };



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



  // style definitions -----------------------------------------------------------

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

    void Reset() {
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



  struct TTextStyle {
    uint16_t color   = 1;
    uint16_t font    = 42;
    uint16_t align   = 12;
    float    spacing = 0.05;

    void SetStyle(const uint16_t col, const uint16_t fon, const uint16_t aln, const float space) {
      color   = col;
      font    = fon;
      align   = aln;
      spacing = space;
      return;
    }  // end 'SetStyle(uin16_t, uint16_t, uint16_t, float)'

    void Reset() {
      color   = 1;
      font    = 42;
      align   = 12;
      spacing = 0.05;
      return;
    }  // end 'Reset()'
  };  // end TTextStyle



  // object definitions -------------------------------------------------------

  struct TAxisDef {
    size_t nbins = 1;
    double start = 0.;
    double stop  = 1.;

    // for variable binning
    std::vector<double> bins;

    void SetBins(const size_t num, const double begin, const double end) {
      nbins = num;
      start = begin;
      stop  = end;
      return;
    }  // end 'SetBins(size_t, double, double)'

    void SetVariableBins(const std::vector<double> vecBins) {
      bins  = vecBins;
      nbins = vecBins.size() + 1;
      return;
    }  // end 'SetVariableBins(size_t, vector<double>)'

    void Reset() {
      nBins = 1;
      start = 0;
      stop  = 1;
      bins.clear();
      return;
    }  // end 'Reset()'
  };  // end 'TAxisDef'



  struct THNDef {
    string name  = "";
    string title = "";

    // axes
    std::array<TAxisDef, _NMaxAxes> axes;

    void SetNameAndTitle(const string nam, const string ttl) {
      name  = nam;
      title = ttl;
      return;
    }  // end 'SetNameAndTitle(string, string)'

    void SetAxis(const TGraphicalUtitlities::Axis axis, const TAxisDef def) {
      axes[axis] = def;
      return;
    }  // end 'SetAxis(TGraphicalUtitlities::Axis, TAxisDef)'

    void Reset() {
      name = "";
      title = "";
      for (auto axis : axes) {
        axis.Reset();
      }
    }  // end 'Reset()'
  };  // end 'THNDef'

}  // end TGraphicalUtitlities namespace

//end -------------------------------------------------------------------------
