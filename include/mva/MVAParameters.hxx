/// ===========================================================================
/*! \file   MVAParameters.hxx
 *  \author Derek Anderson
 *  \date   11.08.2024
 *
 *  Definition of parameters needed to run TMVA
 */
/// ===========================================================================

#ifndef RAU_MVAPARAMETERS_HXX
#define RAU_MVAPARAMETERS_HXX

// c++ utilities
#include <string>
#include <utility>
#include <vector>
// root libraries
#include <TCut.h>
// rau components
#include "MVATools.hxx"



namespace ROOTAnalysisUtilities {
  namespace MVA {

    // ==========================================================================
    //! TMVA Parameters
    // ==========================================================================
    /*! Struct to consolidate training/application
     *  parameters used frequently with TMVA.
     *
     *  FIXME there might be a way to use sub-structs to make
     *  the interface a little nicer...
     *    - Could also add some setters/getters...
     *    - Build in some options to compress vectors of
     *      options...
     */
    struct Parameters {

      // variables & methods
      std::vector<std::pair<Tools::Use,  std::string>> variables;  // input variables & usage
      std::vector<std::pair<std::string, std::string>> methods;    // methods to use & options

      // tmva options
      std::vector<std::string> opts_factory;   // general options
      std::vector<std::string> opts_training;  // training/testing options
      std::vector<std::string> opts_reading;   // reading/evaluating options

      // other parameters
      bool  add_spectators;  // whether or not to add spectator variables
      TCut  training_cuts;   // cuts to apply during training
      TCut  reading_cuts;    // cuts to apply during reading
      float tree_weight;     // weight of tree being trained on

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Parameters()  {};
      ~Parameters() {};

    };  // end Parameters

  }  // end MVA namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
