/// ---------------------------------------------------------------------------
/*! \file   RLabelStyle.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates style information for the labels of an axis
 */
/// ---------------------------------------------------------------------------

#ifndef RLabelStyle_hxx
#define RLabelStyle_hxx



namespace RGraphicalUtilities {
  namespace Attributes {

    // ------------------------------------------------------------------------
    //! Label style
    // ------------------------------------------------------------------------
    struct RLabelStyle {

      // data members
      uint16_t color  = 1;
      uint16_t font   = 42;
      float    size   = 0.04;
      float    alpha  = 0.;
      float    offset = 0.005;

      // set data members
      inline void SetStyle(const uint16_t col, const uint16_t fon, const float siz, const float alp, const float off) {
        color  = col;
        font   = fon;
        size   = siz;
        alpha  = alp;
        offset = off;
        return;
      }  // end 'SetStyle(uint16_t, uint16_t, float, float, float)'

      // reset data members
      inline void Reset() {
        color  = 1;
        font   = 42;
        size   = 0.04;
        alpha  = 0.;
        offset = 0.005;
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      RLabelStyle()  {};
      ~RLabelStyle() {};

      // ctor accepting arguments
      RLabelStyle(const uint16_t col, const uint16_t fon, const float siz, const float alp, const float off) {
        SetStyle(col, fon, siz, alp, off);
      }

    };  // end RLabelStyle

  }  // end Attributes namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
