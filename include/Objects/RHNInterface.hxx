/// ---------------------------------------------------------------------------
/*! \file   RHNInterface.hxx
 *  \author Derek Anderson
 *  \date   08.12.2024
 *
 *  Consolidates interfance to TH{1, 2, 3}'s
 */
/// ---------------------------------------------------------------------------

#ifndef RHNInterface_hxx
#define RHNInterface_hxx

// c++ utilities
#include <array>
// RGU types
#include "../Elements/RAxisDef.hxx"
#include "../Elements/RBinsDef.hxx"



namespace RGraphicalUtilities {
  namespace Objects {

    // ------------------------------------------------------------------------
    //! ND histogram interface
    // ------------------------------------------------------------------------
    struct RHNInterface {

      // name and title
      string name  = "";
      string title = "";

      // axes and bins
      std::array<Elements::RAxisDef, NMaxAxes> axes;
      std::array<Elements::RBinsDef, NMaxAxes> bins;

      // set name and title
      void SetNameAndTitle(const string nam, const string ttl) {
        name  = nam;
        title = ttl;
        return;
      }  // end 'SetNameAndTitle(string, string)'

      // set axis and bins
      void SetAxis(const Types::Axis axis, const Elements::RBinsDef bin, const Elements::RAxisDef axi) {
        bins.at(axis) = bin;
        axes.at(axis) = axi;
        return;
      }  // end 'SetAxis(Types::Axis, Elements::RBinsDef, Elements::RAxisDef)'

      // reset set data members
      void Reset() {
        name  = "";
        title = "";
        for (auto axis : axes) {
          axis.Reset();
        }
        for (auto bin : bins) {
          bin.Reset();
        }
      }  // end 'Reset()'

      // default ctor/dtor
      RHNInterface()  {};
      ~RHNInterface() {};

      // ctor accepting arguments
      /* TODO fill in */

    };  // end RHNInterface

  }  // end Objects namespace
}  // end RGraphicalUtilities namespace

#endif

// end ------------------------------------------------------------------------
