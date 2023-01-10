// 'TGraphicalUtility.h'
// Derek Anderson
// 01.10.2022
//
// A class to streamline interacting
// with graphical objects (e.g.
// histograms) in ROOT

#ifndef TGraphicalUtility_h
#define TGraphicalUtility_h

// standard c includes
/* will go here */

// root includes
#include <TROOT.h>



// class definition -----------------------------------------------------------

class TGraphicalUtility {

  public:

    // attribute styles
    struct TMarkerStyle;
    struct TLineStyle;
    struct TFillStyle;
    struct TAxisStyle;

    // ctor/dtor
    TGraphicalUtility() {};
    ~TGraphicalUtility();

    // set object style
    void set_style(/*auto &to_be_styled*/);

  private:

    // attribute styles setters
    void set_marker_style(/*auto &to_be_styled, */const TMarkerStyle marker_style);
    void set_fill_style(/*auto &to_be_styled, */const TFillStyle fill_style);
    void set_line_style(/*auto &to_be_styled, */const TLineStyle line_style);
    void set_axis_style(/*auto &to_be_styled, */const TAxisStyle axis_style);

};

#endif

// end ------------------------------------------------------------------------
