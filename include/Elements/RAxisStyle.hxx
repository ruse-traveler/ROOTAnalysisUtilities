/// ---------------------------------------------------------------------------
/*! \file   RAxisStyle.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates style information for the labels of an axis
 */
/// ---------------------------------------------------------------------------

#ifndef RAxisStyle_hxx
#define RAxisStyle_hxx

#include "RLabelStyle.hxx"
#include "RTitleStyle.hxx"



namespace RGraphicalUtilities {
  namespace Attributes {

    // ------------------------------------------------------------------------
    //! Axis style
    // ------------------------------------------------------------------------
    struct RAxisStyle {

      RTitleStyle title;
      RLabelStyle label;

      inline void SetStyle(const RTitleStyle ttl, const RLabelStyle lab) {
        title = ttl;
        label = lab;
        return;
      }  // 'SetStyle(RTitleStyle, RLabelStyle)'

      inline void Reset() {
        title.Reset();
        label.Reset();
        return;
      }  // end 'Reset()'

    };  // end RAxisStyle

  }  // end Attributes namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
