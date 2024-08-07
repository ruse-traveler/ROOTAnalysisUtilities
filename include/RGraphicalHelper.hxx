/// ---------------------------------------------------------------------------
/*! \file   RGraphicalHelper.hxx
 *  \author Derek Anderson
 *  \date   08.07.2024
 *
 *  A class to streamline interacting
 *  with graphical objects (e.g.
 *  histograms) in ROOT
 */
/// ---------------------------------------------------------------------------

#ifndef RGraphicalHelper_hxx
#define RGraphicalHelper_hxx

// c++ utilities
#include <string>
#include <vector>
#include <utility>
// root libraries
#include <TPaveText.h>
// graphical utilities
#include "RGraphicalUtilities.hxx"



// ----------------------------------------------------------------------------
//! RGraphicalHelper
// ----------------------------------------------------------------------------
/*! A lightweight class to streamline interacting
 *  with graphical objects in ROOT.
 *
 */
class RGraphicalHelper {

  public:

    // ctor/dtor
    RGraphicalHelper() {};
    ~RGraphicalHelper();

    ///! make a text box using provided text
    ///!   - TODO meat should be moved to a method in the utilities namespace...
    inline TPaveText* MakeTextBox(const SVec vecTxt, const FPair width = {0.1, 0.3}, const float yStart = 0.1, const std::string option = "NDC NB") {

      // determine y-dimensions of box
      const float yStop  = yStart + (vecTxt.size() * _txtStyle.spacing);
      const FPair height = std::make_pair(yStart, yStop);

      // make text box
      TPaveText* ptTxtBox = new TPaveText(width.first, height.first, width.first, height.second, option.data());
      ptTxtBox -> SetTextFont(_txtStyle.font);
      ptTxtBox -> SetTextAlign(_txtStyle.align);
      ptTxtBox -> SetTextColor(_txtStyle.color);
      for (const std::string text : vecText) {
        ptTxtBox -> AddText(text.data());
      }
      return ptTxtBox;

    }  // end 'MakeTextBox(SVec, FPair, float, std::string)'

  private:

    // general options
    RTextStyle _txtStyle;

};

#endif

// end ------------------------------------------------------------------------
