/// ---------------------------------------------------------------------------
/*! \file   RLineStyle.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates style information for TAttLine's
 */
/// ---------------------------------------------------------------------------

#ifndef RLineStyle_hxx
#define RLineStyle_hxx



namespace RGraphicalUtilities {
  namespace Attributes {

    // ------------------------------------------------------------------------
    //! Line style
    // ------------------------------------------------------------------------
    struct RLineStyle {

      // data members
      uint16_t color = 1;
      uint16_t style = 1;
      uint16_t width = 1;
      float    alpha = 0.;

      // set data members
      inline void SetStyle(const uint16_t col, const uint16_t sty, const uint16_t wid, const float alp) {
        color = col;
        style = sty;
        width = wid;
        alpha = alp;
        return;
      }  // end 'SetStyle(uint16_t, uint16_t, uint16_t, float)'

      // reset data members
      inline void Reset() {
        color = 1;
        style = 1;
        width = 1;
        alpha = 0.;
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      RLineStyle()  {};
      ~RLineStyle() {};

      // ctor accepting arguments
      RLineStyle(const uint16_t col, const uint16_t sty, const uint16_t wid, const float alp) {
        SetStyle(col, sty, wid, alp);
      }

    };  // end RLineStyle def

  }  // end Atrributes namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
