/// ===========================================================================
/*! \file   MVATools.hxx
 *  \author Derek Anderson
 *  \date   11.08.2024
 *
 *  Useful tools related to TMVA
 */
/// ===========================================================================

#ifndef RAU_MVATOOLS_HXX
#define RAU_MVATOOLS_HXX

// c++ utilities
#include <algorithm>
#include <cassert>
#include <cmath>
#include <optional>
#include <vector>
// root libraries
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
// tmva components
#include <TMVA/Tools.h>
#include <TMVA/Types.h>
#include <TMVA/Reader.h>
#include <TMVA/Factory.h>
#include <TMVA/DataLoader.h>
// rau componenets
#include "../graph/GraphPoint.hxx"



namespace ROOTAnalysisUtilities {
  namespace Tools {

    // ------------------------------------------------------------------------
    //! Use cases for input variables
    // ------------------------------------------------------------------------
    /*! FIXME this might be better served in a dedicated "Type" or "Constant"
     *  namespace...
     */ 
    enum class Use {Target, Train, Watch};



    // ------------------------------------------------------------------------
    //! Map of method names to algorithm type
    // ------------------------------------------------------------------------
    /*! This map enables automation of booking methods: some variants
     *  of algorithms (e.g. BDTG) cause TMVA to emit a std::runtime_error
     *  when attempting to look up the type based on the method name via
     *  the TMVA::Types helper object.
     *
     *  FIXME this might be better served in a dedicated "Type" or "Constant"
     *  namespace...
     */
    inline std::map<std::string, TMVA::Types::EMVA> MapNameToType() {

      static std::map<std::string, TMVA::Types::EMVA> mapNameToType = {
        {"BDT",      TMVA::Types::EMVA::kBDT},
        {"BDTG",     TMVA::Types::EMVA::kBDT},
        {"DNN",      TMVA::Types::EMVA::kDNN},
        {"FDA_GA",   TMVA::Types::EMVA::kFDA},
        {"FDA_GAMT", TMVA::Types::EMVA::kFDA},
        {"FDA_MC",   TMVA::Types::EMVA::kFDA},
        {"FDA_MT",   TMVA::Types::EMVA::kFDA},
        {"KNN",      TMVA::Types::EMVA::kKNN},
        {"LD",       TMVA::Types::EMVA::kLD},
        {"MLP",      TMVA::Types::EMVA::kMLP},
        {"PDEFoam",  TMVA::Types::EMVA::kPDEFoam},
        {"PDERS",    TMVA::Types::EMVA::kPDERS},
        {"SVM",      TMVA::Types::EMVA::kSVM}
      };
      return mapNameToType;

    }  // end 'MapNameToType()'



    // --------------------------------------------------------------------------
    //! Helper method to check if a file exists or not
    // --------------------------------------------------------------------------
    inline bool DoesFileExist(const std::string& name) {

      if (FILE* file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
      } else {
        return false;
      }

    }  // end 'DoesFileExist(std::string)'



    // --------------------------------------------------------------------------
    //! Helper method to compress vector of strings into a colon-separated list
    // --------------------------------------------------------------------------
    inline std::string CompressList(const std::vector<std::string>& strings) {

      std::string compressed("");
      for (std::size_t iString = 0; iString < strings.size(); ++iString) {
        compressed.append(strings[iString]);
        if (iString + 1 < strings.size()) {
          compressed.append(":");
        }
      }
      return compressed;

    }  // end 'CompressList(std::vector<std::string>&)'

  }  // end Tools namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
