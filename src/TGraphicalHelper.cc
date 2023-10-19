// ----------------------------------------------------------------------------
// 'TGraphicalHelper.cc'
// Derek Anderson
// 01.10.2022
//
// A class to streamline interacting
// with graphical objects (e.g.
// histograms) in ROOT
// ----------------------------------------------------------------------------

#define TGraphicalHelper_cc

// header includes
#include "TGraphicalHelper.hh"

// make common namespaces implicit
using namespace std;
using namespace TGraphicalUtilities;



// makers ---------------------------------------------------------------------

TPaveText* TGraphicalHelper::MakeTextBox(const SVec vecTxt, const FPair width, const float yStart, const string option);

  // determine y-dimensions of box
  const float yStop  = yStart + (vecTxt.size() * _txtStyle.spacing);
  const FPair height = make_pair(yStart, yStop);

  // make text box
  TPaveText* ptTxtBox = new TPaveText(width.first, height.first, width.first, height.second, option.data());
  ptTxtBox -> SetTextFont(_txtStyle.font);
  ptTxtBox -> SetTextAlign(_txtStyle.align);
  ptTxtBox -> SetTextColor(_txtStyle.color);
  for (const string text : vecText) {
    ptTxtBox -> AddText(text.data());
  }
  return ptTxtBox;

}  // end 'MakeTextBox(SVec, FPair, float, string)'

// end ------------------------------------------------------------------------
