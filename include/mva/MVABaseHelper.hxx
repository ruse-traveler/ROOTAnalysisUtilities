/// ===========================================================================
/*! \file   MVABaseHelper.hxx
 *  \author Derek Anderson
 *  \date   11.08.2024
 *
 *  Base class for various TMVA helpers.
 */
/// ===========================================================================

#ifndef RAU_MVABASEHELPER_hxx
#define RAU_MVABASEHELPER_hxx

// c++ utilities
#include <map>
#include <string>
#include <vector>
// rau components
#include "MVATools.hxx"



namespace ROOTAnalysisUtilities {
  namespace MVA {

    // ==========================================================================
    //! Base Helper
    // ==========================================================================
    /*! Base TMVA Helper class that the training and
     *  reading helpers inherit from. Defines common
     *  methods used betwene the two.
     *
     *  FIXME integrating the helpers w/ the parameters
     *  more tightly might make things cleaner...
     */
    class BaseHelper {

      protected:

        // data members
        std::vector<std::string>           m_watchers;
        std::vector<std::string>           m_trainers;
        std::vector<std::string>           m_targets;
        std::vector<std::string>           m_methods;
        std::map<std::string, std::string> m_opts_method;

        // ----------------------------------------------------------------------
        //! Set methods to use
        // ----------------------------------------------------------------------
        inline void SetMethods(const std::vector<std::pair<std::string, std::string>>& methods) {

          for (const auto& methodAndOpt : methods) {
            m_methods.push_back( methodAndOpt.first );
            m_opts_method[methodAndOpt.first] = methodAndOpt.second;
          }
          return;

        }  // end 'SetMethods(std::vector<std::string>&)'

        // ----------------------------------------------------------------------
        //! Set input variables
        // ----------------------------------------------------------------------
        inline void SetInputVariables(const std::vector<std::pair<Tools::Use, std::string>>& inputs) {

          // assign input leaf to relevant vector
          for (const auto& input : inputs) {
            switch (input.first) {
              case Tools::Use::Target:
                m_targets.push_back( input.second );
                break;
              case Tools::Use::Train:
                m_trainers.push_back( input.second );
                break;
              case Tools::Use::Watch:
                [[fallthrough]];
              default:
                m_watchers.push_back( input.second );
                break;
            }
          }  // end input loop
          return;

        }  // end 'SetInputVariables(std::vector<std::pair<Use, std::string>>&)'

      public:

        // ----------------------------------------------------------------------
        //! Getters
        // ----------------------------------------------------------------------
        inline std::vector<std::string> GetMethods()    const {return m_methods;}
        inline std::vector<std::string> GetSpectators() const {return m_watchers;}
        inline std::vector<std::string> GetTrainers()   const {return m_trainers;}
        inline std::vector<std::string> GetTargets()    const {return m_targets;}

        // ----------------------------------------------------------------------
        //! Default ctor/dtor
        // ----------------------------------------------------------------------
        BaseHelper()  {};
        ~BaseHelper() {};

    };  // end BaseHelper

  }  // end MVA namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
