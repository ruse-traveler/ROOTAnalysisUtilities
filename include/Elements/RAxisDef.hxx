/// ---------------------------------------------------------------------------
/*! \file   RAxisDef.hxx
 *  \author Derek Anderson
 *  \date   08.09.2024
 *
 *  Consolidates axis definition
 */
/// ---------------------------------------------------------------------------

#ifndef RAxisDef_hxx
#define RAxisDef_hxx

// RGU types
#include "../Attributes/RLabelStyle.hxx"
#include "../Attributes/RTitleStyle.hxx"



namespace RGraphicalUtilities {
  namespace Elements {

    // ------------------------------------------------------------------------
    //! Axis definition
    // ------------------------------------------------------------------------
    struct RAxisDef {

      // data members
      Attributes::RTitleStyle title;
      Attrubites::RLabelStyle label;

      // set data members
      inline void SetDefinition(const Attributes::RTitleStyle ttl, const Attributes::RLabelStyle lab) {
        title = ttl;
        label = lab;
        return;
      }  // 'SetStyle(RTitleStyle, RLabelStyle)'

      // reset data members
      inline void Reset() {
        title.Reset();
        label.Reset();
        return;
      }  // end 'Reset()'

      // default ctor/dtor
      RAxisDef()  {};
      ~RAxisDef() {};

      // ctor accepting arguments
      RAxisDef(const Attributes::RTitleStyle ttl, const Attributes::RLabelStyle lab) {
        SetDefinition(ttl, lab);
      }

    };  // end RAxisDef

  }  // end Elements namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
