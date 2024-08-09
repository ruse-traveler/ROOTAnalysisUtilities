/// ---------------------------------------------------------------------------
/*! \file   RTitleStyle.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates style information for the title of a axis,
 *  histogram, etc.
 */
/// ---------------------------------------------------------------------------

#ifndef RTitleStyle_hxx
#define RTitleStyle_hxx

// c++ utiilities
#include <string>



namespace RGraphicalUtilities {
  namespace Attributes {

    // ------------------------------------------------------------------------
    //! Title style
    // ------------------------------------------------------------------------
    struct RTitleStyle {

      // data members
      uint16_t color  = 1;
      uint16_t center = 0;
      uint16_t font   = 42;
      float    size   = 0.04;
      float    alpha  = 0.;
      float    offset = 1.1;
      string   title  = "";

      // set data members
      inline void SetStyle(
        const uint16_t col,
        const uint16_t cen,
        const uint16_t fon,
        const float siz,
        const float alp,
        const float off,
        const string ttl
      ) {
        color  = col;
        center = cen;
        font   = fon;
        size   = siz;
        alpha  = alp;
        offset = off;
        title  = ttl;
        return;
      }  // end 'SetStyle(uint16_t, uint16_t, uint16_t, float, float, float, string)'

      // reset data members
      inline void Reset() {
        color  = 1;
        center = 0;
        font   = 42;
        size   = 0.04;
        alpha  = 0.;
        offset = 1.1;
        title  = "";
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      RTitleStyle()  {};
      ~RTitleStyle() {};

      // ctor accepting arguments
      RTitleStyle(
        const uint16_t col,
        const uint16_t cen,
        const uint16_t fon,
        const float siz,
        const float alp,
        const float off,
        const string ttl
      ) {
        SetStyle(col, cen, fon, siz, alp, off, ttl);
      }

    };  // end RTitleStyle

  }  // end Attributes namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
