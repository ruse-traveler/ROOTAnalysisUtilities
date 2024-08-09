/// ---------------------------------------------------------------------------
/*! \file   RTextStyle.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates style information for text
 */
/// ---------------------------------------------------------------------------

#ifndef RTextStyle_hxx
#define RTextStyle_hxx



namespace RGraphicalUtilities {
  namespace Attributes {

    // ------------------------------------------------------------------------
    //! Text style
    // ------------------------------------------------------------------------
    struct RTextStyle {

      // data members
      uint16_t color   = 1;
      uint16_t font    = 42;
      uint16_t align   = 12;
      float    spacing = 0.05;

      // set data members
      inline void SetStyle(const uint16_t col, const uint16_t fon, const uint16_t aln, const float space) {
        color   = col;
        font    = fon;
        align   = aln;
        spacing = space;
        return;
      }  // end 'SetStyle(uin16_t, uint16_t, uint16_t, float)'

      // reset data members
      inline void Reset() {
        color   = 1;
        font    = 42;
        align   = 12;
        spacing = 0.05;
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      RTextStyle()  {};
      ~RTextStyle() {};

      // ctor accepting arguments
      RTextStyle(const uint16_t col, const uint16_t fon, const uint16_t aln, const float space) {
        SetStyle(col, fon, aln, space);
      }

    };  // end RTextStyle

  }  // end Attributes namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
