/// ===========================================================================
/*! \file   PlotterTools.hxx
 *  \author Derek Anderson
 *  \date   12.27.2024
 *
 *  Useful tools for plotter classes.
 */
/// ===========================================================================

#ifndef RAU_PLOTTERTOOLS_HXX
#define RAU_PLOTTERTOOLS_HXX

// c++ utilities
#include <cassert>
#include <string>
// root libraries
#include <TFile.h>
#include <TObject.h>



namespace ROOTAnalysisUtilities {
  namespace Tools {

    // ========================================================================
    //! Open file and check if good
    // ========================================================================
    TFile* OpenFile(const std::string& name, const std::string& option) {

      // try to open file, throw error if not able
      TFile* file = new TFile( name.data(), option.data() );
      if (!file) {
        std::cerr << "PANIC: couldn't open file!\n"
                  << "       file = " << name << "\n"
                  << std::endl;
        assert(file);
      }

      // then check file by cd'ing into it
      const bool isGoodCD = file -> cd();
      if (!isGoodCD) {
        std::cerr << "PANIC: couldn't cd into file!\n"
                  << "       file = " << name << "\n"
                  << std::endl;
        assert(isGoodCD);
      }
      return file;

    }  // end 'OpenFile(std::string&, std::string&)'



    // ========================================================================
    //! Grab an object from a file
    // ========================================================================
    TObject* GrabObject(const std::string& object, TFile* file) {

      // try to grab object from file, throw error if not able
      TObject* grabbed = (TObject*) file -> Get( object.data() );
      if (!grabbed) {
        std::cerr << "PANIC: couldn't grab object!\n"
                 << "       file   = " << file   << "\n"
                 << "       object = " << object << "\n"
                 << std::endl;
        assert(grabbed);
      }
      return grabbed;

    }  // end 'GrabObject(std::string&, TFile*)'

  }  // end Tools namespace
}    // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
