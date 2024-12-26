/// ===========================================================================
/*! \file   MVATrainHelper.hxx
 *  \author Derek Anderson
 *  \date   11.08.2024
 *
 *  Helper for training models w/ TMVA.
 */
/// ===========================================================================

#ifndef RAU_MVATRAINHELPER_hxx
#define RAU_MVATRAINHELPER_hxx

// c++ utilities
#include <map>
#include <string>
#include <vector>
// tmva components
#include <TMVA/Factory.h>
#include <TMVA/DataLoader.h>
// rau components
#include "MVABaseHelper.hxx"
#include "MVATools.hxx"
#include "MVATypes.hxx"



namespace ROOTAnalysisUtilities {
  namespace MVA {

    // ==========================================================================
    //! Training Helper
    // ==========================================================================
    /*! A small class to help training via
     *  models ROOT TMVA.
     *
     *  FIXME integrating the helpers w/ the parameters
     *  more tightly might make things cleaner...
     */
    class TrainHelper : public BaseHelper {

      private:

        // data members
        std::vector<std::string> m_opts_factory;
        std::vector<std::string> m_opts_train;

      public:

        // ----------------------------------------------------------------------
        //! Compress lists into colon-separated ones
        // ----------------------------------------------------------------------
        inline std::string CompressFactoryOptions()  const {return Tools::CompressList(m_opts_factory);}
        inline std::string CompressTrainingOptions() const {return Tools::CompressList(m_opts_train);}

        // ----------------------------------------------------------------------
        //! Getters
        // ----------------------------------------------------------------------
        inline std::vector<std::string> GetFactoryOptions()  const {return m_opts_factory;}
        inline std::vector<std::string> GetTrainingOptions() const {return m_opts_train;}

        // ----------------------------------------------------------------------
        //! Setters
        // ----------------------------------------------------------------------
        inline void SetTrainOptions(const std::vector<std::string>& options)   {m_opts_train   = options;}
        inline void SetFactoryOptions(const std::vector<std::string>& options) {m_opts_factory = options;}

        // ----------------------------------------------------------------------
        //! Add variables to data loader
        // ----------------------------------------------------------------------
        inline void LoadVariables(TMVA::DataLoader* loader, const bool add_watchers = false) {

          // add targets
          for (const std::string& target : m_targets) {
            loader -> AddTarget(target);
          }

          // add training variables
          for (const std::string& train : m_trainers) {
            loader -> AddVariable(train);
          }

          // if needed, add spectators
          if (add_watchers) {
            for (const std::string& spec : m_watchers) {
              loader -> AddSpectator(spec);
            }
          }
          return;

        }  // end 'LoadVariables(TMVA::DataLoader*, bool)'

        // ------------------------------------------------------------------------
        //! Book methods to train
        // ------------------------------------------------------------------------
        inline void BookMethodsToTrain(TMVA::Factory* factory, TMVA::DataLoader* loader) {

          // book each method currently set
          for (const std::string& method : m_methods) {
            factory -> BookMethod(
              loader,
              Tools::MapNameToType()[method],
              method.data(),
              m_opts_method[method].data()
            );
          }
          return;

        }  // end 'BookMethodsToTrain(TMVA::Factory*, TMVA::DataLoader*)'

        // ----------------------------------------------------------------------
        //! Default ctor/dtor
        // ----------------------------------------------------------------------
        TrainHelper()  {};
        ~TrainHelper() {};

        // ----------------------------------------------------------------------
        //! ctor accepting a list of variable-use pairs and a list of methods
        // ----------------------------------------------------------------------
        TrainHelper(
          const std::vector<std::pair<Types::Use, std::string>>& inputs,
          const std::vector<std::pair<std::string, std::string>>& methods
        ) {

          SetInputVariables(inputs);
          SetMethods(methods);

        }  // end ctor(std::vector<std::pair<Types::Use, std::string>>&, std::vector<std::string>&)'

    };  // end TrainHelper

  }  // end MVA namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
