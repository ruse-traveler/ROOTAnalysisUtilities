/// ---------------------------------------------------------------------------
/*! \file   TestGraphicalUtility.cxx
 *  \author Derek Anderson
 *  \date   08.97.2024
 *
 *  A short unit test for the
 *  RGraphicalUtility library.
 */
/// ---------------------------------------------------------------------------

#ifndef TestGraphicalUtility_cxx
#define TestGraphicalUtility_cxx

// c++ utilities
#include <utility>
// root libraries
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
// graphical utility include
#include <include/RGraphicalUtility.hxx>



TEST_CASE("TestGraphicalUtility") {

  /* TODO create test objects here */

  // instantiate helper
  std::unique_ptr<RGraphicalHelper> helper = std::make_unique<RGraphicalHelper>();

  /* TODO do things with utility here */

}  // end test case

#endif

// end ------------------------------------------------------------------------
