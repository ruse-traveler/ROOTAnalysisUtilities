/// ===========================================================================
/*! \file   GraphDefinition.hxx
 *  \author Derek Anderson
 *  \date   10.21.2024
 *
 *  Interface to TGraph and derived classes.
 */
/// ===========================================================================

#ifndef RAU_GRAPHDEFINITION_HXX
#define RAU_GRAPHDEFINITION_HXX

// c++ utilities
#include <string>
#include <vector>
// root libraries
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
// library components
#include "GraphPoint.hxx"



namespace ROOTAnalysisUtilities {
  namespace Graph {

    // ========================================================================
    //! Graph definition
    // ========================================================================
    /*! A small class to consolidate necessary data
     *  to define a TGraph, TGraphErrors, or
     *  TGraphAsymmErrors
     */ 
    class Definition {

      private:

        // options for accessing specific members of a point
        enum class Member {X, Y, EX, EXlo, EXhi, EY, EYlo, EYhi};

        // data members
        std::string        m_name;
        std::vector<Point> m_points;

        // --------------------------------------------------------------------
        //! Helper method to pull a vector of x, y, etc. from a vector of points
        // --------------------------------------------------------------------
        std::vector<double> GetMembers(const Member member) const {

          std::vector<double> members;
          for (const auto& point : m_points) {

            // select relevant member
            switch (member) {

              case Member::X:
                members.push_back(point.x);
                break;

              case Member::Y:
                members.push_back(point.y);
                break;

              case Member::EX:
                members.push_back(point.ex);
                break;

              case Member::EXlo:
                members.push_back(point.ex_lo);
                break;

              case Member::EXhi:
                members.push_back(point.ex_hi);
                break;

              case Member::EY:
                members.push_back(point.ey);
                break;

              case Member::EYlo:
                members.push_back(point.ey_lo);
                break;

              case Member::EYhi:
                members.push_back(point.ey_hi);
                break;

              // by default return nothing
              default:
                break;

            }  // end switch(member)
          }  // end point loop
          return members;

        }  // end 'GetMembers(Member)'

      public:

        // --------------------------------------------------------------------
        //! Getters
        // --------------------------------------------------------------------
        std::string        GetName()   const {return m_name;}
        std::vector<Point> GetPoints() const {return m_points;}

        // --------------------------------------------------------------------
        //! Setters
        // --------------------------------------------------------------------
        void SetName(const std::string& name)            {m_name = name;}
        void SetPoints(const std::vector<Point>& points) {m_points = points;}

        // --------------------------------------------------------------------
        //! Reset points
        // --------------------------------------------------------------------
        void ResetPoints() {

          m_points.clear();
          return;

        }  // end 'ResetPoints()'

        // --------------------------------------------------------------------
        //! Add a point
        // --------------------------------------------------------------------
        void AddPoint(const Point& point) {

          m_points.push_back(point);
          return;

        }  // end 'AddPoint(Point&)'

        // --------------------------------------------------------------------
        //! Make a TGraph
        // --------------------------------------------------------------------
        TGraph* MakeTGraph() const {

          // decompose points
          std::vector<double> x_vals = GetMembers(Member::X);
          std::vector<double> y_vals = GetMembers(Member::Y);

          // create TGraph
          TGraph* graph = new TGraph(
            m_points.size(),
            x_vals.data(),
            y_vals.data()
          );
          graph -> SetName(m_name.data());
          return graph;

        }  // end 'MakeTGraph()'

        // --------------------------------------------------------------------
        //! Make a TGraphErrors
        // --------------------------------------------------------------------
        TGraphErrors* MakeTGraphErrors() const {

          // decompose points
          std::vector<double> x_vals = GetMembers(Member::X);
          std::vector<double> y_vals = GetMembers(Member::Y);
          std::vector<double> x_errs = GetMembers(Member::EX);
          std::vector<double> y_errs = GetMembers(Member::EY);

          // create TGraph
          TGraphErrors* graph = new TGraphErrors(
            m_points.size(),
            x_vals.data(),
            y_vals.data(),
            x_errs.data(),
            y_errs.data()
          );
          graph -> SetName(m_name.data());
          return graph;

        }  // end 'MakeTGraphErrors()'

        // --------------------------------------------------------------------
        //! Make a TGraphAsymmErrors
        // --------------------------------------------------------------------
        TGraphAsymmErrors* MakeTGraphAsymmErrors() const {

          // decompose points
          std::vector<double> x_vals    = GetMembers(Member::X);
          std::vector<double> y_vals    = GetMembers(Member::Y);
          std::vector<double> x_lo_errs = GetMembers(Member::EXlo);
          std::vector<double> x_hi_errs = GetMembers(Member::EXhi);
          std::vector<double> y_lo_errs = GetMembers(Member::EYlo);
          std::vector<double> y_hi_errs = GetMembers(Member::EYhi);

          // create TGraph
          TGraphAsymmErrors* graph = new TGraphAsymmErrors(
            m_points.size(),
            x_vals.data(),
            y_vals.data(),
            x_lo_errs.data(),
            x_hi_errs.data(),
            y_lo_errs.data(),
            y_hi_errs.data()
          );
          graph -> SetName(m_name.data());
          return graph;

        }  // end 'MakeTGraphAsymmErrors()'

        // --------------------------------------------------------------------
        //! default ctor/dtor
        // --------------------------------------------------------------------
        Definition()  {};
        ~Definition() {};

        // --------------------------------------------------------------------
        //! ctor accepting a name
        // --------------------------------------------------------------------
        Definition(const std::string& name) {

          SetName(name);

        }  // end ctor(std::string)

    };  // end Definition

  }  // end Graph namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
