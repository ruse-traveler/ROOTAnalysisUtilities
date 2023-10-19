// ----------------------------------------------------------------------------
// 'TGraphicalHelper.hh'
// Derek Anderson
// 01.10.2022
//
// A class to streamline interacting
// with graphical objects (e.g.
// histograms) in ROOT
// ----------------------------------------------------------------------------

#ifndef TGraphicalHelper_hh
#define TGraphicalHelper_hh

// standard c includes
#include <string>
#include <vector>
#include <utility>
// root includes
#include <TROOT.h>
#include <TLegend.h>
#include <TPaveText.h>
// helper namespace
#include "TGraphicalUtilities.hh"

// make common namespaces implicit
using namespace std;
using namespace TGraphicalUtilities;


// TGraphicalHelper definition -----------------------------------------------

class TGraphicalHelper {

  public:

    // ctor/dtor
    TGraphicalHelper() {};
    ~TGraphicalHelper();

    // makers
    TPaveText* MakeTextBox(const SVec vecTxt, const FPair width = {0.1, 0.3}, const float yStart = 0.1, const string option = "NDC NB");

  private:

    // general options
    TTextStyle _txtStyle;

};

#endif

// end ------------------------------------------------------------------------
