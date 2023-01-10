// 'TestGraphicalUtility.C'
// Derek Anderson
// 01.10.2022
//
// A short macro to test the
// use of the TGraphicalUtility
// class

#ifndef TESTGRAPHICALUTILITY_C
#define TESTGRAPHICALUTILITY_C

// root includes
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <TString.h>
#include <TCanvas.h>
// graphical utility include
#include </sphenix/u/danderson/install/include/tgraphicalutility/TGraphicalUtility.h>

// load graphical utility library
R__LOAD_LIBRARY(/sphenix/u/danderson/install/lib/libtgraphicalutility.so)



void TestGraphicalUtility() {

  /* TODO create test objects here */

  // instantiate utility
  TGraphicalUtility *utility = new TGraphicalUtility();

  /* TODO do things with utility here */
  return;

}  // end 'TestGraphicalUtility()'


#endif

// end ------------------------------------------------------------------------
