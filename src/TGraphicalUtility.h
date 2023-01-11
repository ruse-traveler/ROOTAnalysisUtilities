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

    // enums
    enum Axis { x, y, z };

    // attribute styles
    struct TMarkerStyle;
    struct TLineStyle;
    struct TFillStyle;
    struct TAxisStyle;

    // ctor/dtor
    TGraphicalUtility() {};
    ~TGraphicalUtility();

    // set object style
    template <typename Type> void set_style(Type *to_be_styled);

  private:

    // attribute styles setters
    template <typename Type> void set_marker_style(Type *to_be_styled, const TMarkerStyle style);
    template <typename Type> void set_fill_style(Type *to_be_styled, const TFillStyle style);
    template <typename Type> void set_line_style(Type *to_be_styled, const TLineStyle style);
    template <typename Type> void set_axis_style(Type *to_be_styled, const TAxisStyle style, const Axis axis);

};

#endif

// end ------------------------------------------------------------------------
