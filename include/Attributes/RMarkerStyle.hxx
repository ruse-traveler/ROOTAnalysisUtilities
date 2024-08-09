/// ---------------------------------------------------------------------------
/*! \file   RMarkerStyle.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates style information for TAttMarker's
 */
/// ---------------------------------------------------------------------------

#ifndef RMarkerStyle_hxx
#define RMarkerStyle_hxx



namespace RGraphicalUtitlities {
  namespace Attributes {

    // ------------------------------------------------------------------------
    //! Marker style
    // ------------------------------------------------------------------------
    struct RMarkerStyle {

      // data members
      uint16_t color = 1;
      uint16_t style = 1;
      float    alpha = 0.;
      float    size  = 1.;

      // set data members
      inline void SetStyle(const uint16_t col, const uint16_t sty, const float alp, const float siz) {
        color = col;
        style = sty;
        alpha = alp;
        size  = siz;
        return;
      }  // end 'SetStyle(uint16_t, uint16_t, float, float)'

      // reset data members
      inline void Reset() {
        color = 1;
        style = 1;
        alpha = 0.;
        size  = 1.;
        return;
      }  // end 'Reset()' 

      // default ctor/dtor
      RMakerStyle()  {};
      ~RMakerStyle() {};

      // ctor accepting arguments
      RMarkerStyle(const uint16_t col, const uint16_t sty, const float alp, const float siz) {
        SetStyle(col, sty, alp, siz);
      }

    };  // end RMarkerStyle

  }  // end Attributes namespace
}  // end RGraphicalUtitlities namespace

#endif

// end ------------------------------------------------------------------------
