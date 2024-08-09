/// ---------------------------------------------------------------------------
/*! \file   RFillStyle.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates style information for TAttFill's
 */
/// ---------------------------------------------------------------------------

#ifndef RFillStyle_hxx
#define RFillStyle_hxx



namespace RGraphicalUtilities {
  namespace Attributes {

    // ------------------------------------------------------------------------
    //! Fill style
    // ------------------------------------------------------------------------
    struct RFillStyle {

      // data members
      uint16_t color = 1;
      uint16_t style = 1;
      float    alpha = 0.;

      // set data members
      inline void SetStyle(const uint16_t col, const uint16_t sty, const float alp) {
        color = col;
        style = sty;
        alpha = alp;
        return;
      }  // end 'SetStyle(uint16_t, uint16_t, float)'

      // reset data members
      inline void Reset() {
        color = 1;
        style = 1;
        alpha = 0.;
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      RFillStyle()  {};
      ~RFillStyle() {};

      // ctor accepting arguments
      RFillStyle(const uint16_t col, const uint16_t sty, const float alp) {
        SetStyle(col, sty, alp);
      }

    };  // end RFillStyle

  }  // end Attributes namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
