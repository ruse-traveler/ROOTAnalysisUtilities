/// ===========================================================================
/*! \file   MVAReadHelper.hxx
 *  \author Derek Anderson
 *  \date   11.08.2024
 *
 *  Helper for applying models w/ TMVA.
 */
/// ===========================================================================

#ifndef RAU_MVAREADHELPER_hxx
#define RAU_MVAREADHELPER_hxx

// c++ utilities
#include <map>
#include <string>
#include <vector>
// root libraries
#include <TString.h>
// tmva components
#include <TMVA/Reader.h>
// rau components
#include "../ntuple/NTupleHelper.hxx"
#include "MVABaseHelper.hxx"
#include "MVATools.hxx"
#include "MVATypes.hxx"



namespace ROOTAnalysisUtilities {
  namespace MVA {

    // ==========================================================================
    //! Reading Helper
    // ==========================================================================
    /*! A small class to help reading/evaluating
     *  modles via ROOT TMVA.
     *
     *  FIXME integrating the helpers w/ the parameters
     *  more tightly might make things cleaner...
     */
    class ReadHelper : public BaseHelper {

      private:

        // data members
        std::vector<bool>                  m_read;
        std::vector<float>                 m_outvals;
        std::vector<std::string>           m_outvars;
        std::vector<std::string>           m_options;
        std::map<std::string, std::size_t> m_outdex;

        // ----------------------------------------------------------------------
        //! Generate list of regression outputs
        // ----------------------------------------------------------------------
        /*! Will generate list of targets and the regression
         *  outputs. Every specified target will be evaluated
         *  for every specified method.
         */
        inline void GenerateRegressionOutputs() {

          // first load targets
          std::size_t iOut = 0;
          for (const std::string& target : m_targets) {
            m_outvars.push_back( target );
            m_outdex[ m_outvars.back() ] = iOut;
            ++iOut;
          }

          // then generate list of regression outputs
          for (const std::string& method : m_methods) {
            for (const std::string& target : m_targets) {
              m_outvars.push_back( target + "_" + method );
              m_outdex[ m_outvars.back() ] = iOut;
              ++iOut;
            }
          }

          // resize values vector acordingly & exit
          m_outvals.resize(iOut);
          return;

        }  // end 'GenerateRegressionOutputs()'

      public:

        // ----------------------------------------------------------------------
        //! Compress list into colon-separated one
        // ----------------------------------------------------------------------
        inline std::string CompressOptions() const {return Tools::CompressList(m_options);}

        // ------------------------------------------------------------------------
        //! Setters
        // ------------------------------------------------------------------------
        inline void SetOptions(const std::vector<std::string>& options) {m_options = options;}

        // ----------------------------------------------------------------------
        //! Getters
        // ----------------------------------------------------------------------
        inline std::vector<std::string> GetOptions() const {return m_options;}
        inline std::vector<std::string> GetOutputs() const {return m_outvars;}

        // ----------------------------------------------------------------------
        //! Get a specific output variable
        // ----------------------------------------------------------------------
        inline float GetVariable(const std::string& var) {

          // check if variable exists
          if (!m_outdex.count(var)) {
            assert(m_outdex.count(var));
          }

          // then get variable
          return m_outvals.at(m_outdex[var]);

        }  // end 'GetVariable(std::string&)'

        // ----------------------------------------------------------------------
        //! Reset output values
        // ----------------------------------------------------------------------
        inline void ResetValues() {

          std::fill(
            m_outvals.begin(),
            m_outvals.end(),
            -1. * std::numeric_limits<float>::max()
          );
          return;

        }  // end 'ResetValues()'

        // ----------------------------------------------------------------------
        //! Add NTuple variables to reader
        // ----------------------------------------------------------------------
        inline void ReadVariables(TMVA::Reader* reader, NTupleHelper& helper) const {

          for (const std::string& train : m_trainers) {
            if (!helper.m_index.count(train)) {
              std::cerr << "WARNING: trying to add variable '" << train << "' which is not in input NTuple!" << std::endl;
              continue;
            } else {
              reader -> AddVariable(train.data(), &helper.m_values.at(helper.m_index[train]));
            }
          }
          return;

        }  // end 'ReadVariables(TMVA::Reader*, NTupleHelper&)'

        // ----------------------------------------------------------------------
        //! Book methods to read by providing the path to a directory
        // ----------------------------------------------------------------------
        /*! For each method stored, helper will check for a weights file with
         *  a name conforming to "<method>.weights.xml" in the directory specified
         *  by `directory`. If the file exists, helper will book the method to be
         *  evaulated with that file.
         */
        inline void BookMethodsToRead(
          TMVA::Reader* reader,
          const std::string& directory,
          const std::string& name
        ) {

          // reserve space for each method
          m_read.resize( m_methods.size(), true );

          // loop over all methods
          for (std::size_t iMethod = 0; iMethod < m_methods.size(); ++iMethod) {

            // construct full path
            const std::string path = directory + "/weights/" + name + "_" + m_methods[iMethod] + ".weights.xml";

            // skip if file does not exist
            if (!Tools::DoesFileExist(path)) {
              std::cerr << "WARNING: file '" << path << "' doesn't exist! Not booking method!" << std::endl;
              m_read.at(iMethod) = false;
              continue;
            }

            // otherwise, construct title and book method
            const std::string title = m_methods[iMethod] + " method";
            reader -> BookMVA(title, path);

          }  // end method loop
          return;

        }  // end 'BookMethodsToRead(TMVA::Reader*, std::string&, std::string&)'

        // ----------------------------------------------------------------------
        //! Book methods to read by providing a list of weight files
        // ----------------------------------------------------------------------
        /*! For file passed, helper wil check if file exists and, if it does,
         *  book the corresponding method to be evaluated with that file. This
         *  assumes that the insertion order is the same between the methods
         *  list and the provided list of files.
         */
        inline void BookMethodsToRead(
          TMVA::Reader* reader,
          const std::vector<std::string>& files
        ) {

          // reserve space for each method
          m_read.resize( m_methods.size(), true );

          // make sure input list has same dimension as method list
          if (files.size() != m_methods.size()) {
            assert(files.size() == m_methods.size());
          }

          // loop over provided files
          for (std::size_t iFile = 0; iFile < files.size(); ++iFile) {

            // skip if file does not exist
            if (!Tools::DoesFileExist(files[iFile])) {
              std::cerr << "WARNING: file '" << files[iFile] << "' doesn't exist! Not booking method '" << m_methods.at(iFile) <<"'!" << std::endl;
              m_read.at(iFile) = false;
              continue;
            }

            // otherwise, construct title and book method
            const std::string title = m_methods.at(iFile) + " method";
            reader -> BookMVA(title, files[iFile]);

          }  // end file loop
          return;

        }  // end 'BookMethodsToRead(TMVA::Reader*, std::vector<std::string>&)'

        // ----------------------------------------------------------------------
        //! Evaluate all booked methods
        // ----------------------------------------------------------------------
        inline void EvaluateMethods(TMVA::Reader* reader, NTupleHelper& helper) {

          // loop over all methods
          for (std::size_t iMethod = 0; iMethod < m_methods.size(); ++iMethod) {

            // if not evaluating method, continue
            if (!m_read[iMethod]) {
              continue;
            }

            // construct title & run evaluation
            const std::string        title   = m_methods[iMethod] + " method";
            const std::vector<float> targets = reader -> EvaluateRegression(title);

            // collect regression output
            for (std::size_t iTarget = 0; iTarget < m_targets.size(); ++iTarget) {
              const std::string output = m_targets[iTarget] + "_" + m_methods[iMethod];
              m_outvals.at(m_outdex[output]) = targets.at(iTarget);
            }
          }  // end method loop

          // then collect training targets in output
          for (const std::string& target : m_targets) {
            m_outvals.at(m_outdex[target]) = helper.GetVariable( target );
          }
          return;

        }  // end 'EvaluateMethods(TMVA::Reader*, NTupleHelper&)'

        // ----------------------------------------------------------------------
        //! Default ctor/dtor
        // ----------------------------------------------------------------------
        ReadHelper()  {};
        ~ReadHelper() {};

        // ----------------------------------------------------------------------
        //! ctor accepting a list of variable-use pairs and a list of methods
        // ----------------------------------------------------------------------
        ReadHelper(
          const std::vector<std::pair<Types::Use, std::string>>& inputs,
          const std::vector<std::pair<std::string, std::string>>& methods
        ) {

          SetInputVariables(inputs);
          SetMethods(methods);
          GenerateRegressionOutputs();

        }  // end ctor(std::vector<std::pair<Types::Use, std::string>>&, std::vector<std::string>&)'

    };  // end ReadHelper

  }  // end MVA namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
