/// ===========================================================================
/*! \file   GraphHelper.hxx
 *  \author Derek Anderson
 *  \date   09.29.2024
 *
 *  A lightweight namespace to help work with graphs.
 */
/// ===========================================================================

#ifndef GraphHelper_hxx
#define GraphHelper_hxx

// c++ utilities
#include <map>
#include <limits>
#include <string>
#include <vector>
#include <cassert>
#include <utility>
#include <optional>
#include <algorithm>
// root libraries
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>



namespace ROOTAnalysisUtilities {

  // ============================================================================
  //! Graph Helper
  // ============================================================================
  /*! A small namespace to help work with
   *  ROOT graphs.
   *
   *  TODO split up into headers, organize
   */
  namespace GraphHelper {

    // ==========================================================================
    //! Point
    // ==========================================================================
    /*! A small struct to consolidate data
     *  for a point on a graph
     */
    struct Point {

      // members
      double x;
      double y;
      double ex;
      double ex_lo;
      double ex_hi;
      double ey;
      double ey_lo;
      double ey_hi;

      // ------------------------------------------------------------------------
      //! default ctor/dtor
      // ------------------------------------------------------------------------
      Point()  {};
      ~Point() {};

      // ------------------------------------------------------------------------
      //! ctor without errors
      // ------------------------------------------------------------------------
      Point(const double x_arg, const double y_arg) {

        x     = x_arg;
        y     = y_arg;
        ex    = 0.;
        ex_lo = 0.;
        ex_hi = 0.;
        ey    = 0.;
        ey_lo = 0.;
        ey_hi = 0.;

      }  // end ctor(double, double)

      // ------------------------------------------------------------------------
      //! ctor accepting symmetric errors
      // ------------------------------------------------------------------------
      Point(
        const double x_arg,
        const double y_arg,
        const double ex_arg,
        const double ey_arg
      ) {

        x     = x_arg;
        y     = y_arg;
        ex    = ex_arg;
        ex_lo = ex_arg / 2.;
        ex_hi = ex_arg / 2.;
        ey    = ey_arg;
        ey_lo = ey_arg / 2.;
        ey_hi = ey_arg / 2.;

      }  // end ctor(double, double, double, double)'

      // ------------------------------------------------------------------------
      //! ctor accepting asymmetric errors
      // ------------------------------------------------------------------------
      Point(
        const double x_arg,
        const double y_arg,
        const std::pair<double, double> ex_arg,
        const std::pair<double, double> ey_arg
      ) {

        x     = x_arg;
        y     = y_arg;
        ex_lo = ex_arg.first;
        ex_hi = ex_arg.second;
        ex    = ex_arg.first + ex_arg.second;
        ey_lo = ey_arg.first;
        ey_hi = ey_arg.second;
        ey    = ey_arg.first + ey_arg.second;

      }  // end ctor(double, double, std::pair<double, double>, std::pair<double, double>)

    };   // end Point 



    // ==========================================================================
    //! Graph definition
    // ==========================================================================
    /*! A small class to consolidate necessary data
     *  to define a TGraph, TGraphErrors, or
     *  TGraphAsymmErrors
     */ 
    class Definition {

      private:

        // options for accessing specific members of a point
        enum Member {X, Y, EX, EXlo, EXhi, EY, EYlo, EYhi};

        // data members
        std::string        m_name;
        std::vector<Point> m_points;

        // ----------------------------------------------------------------------
        //! Helper method to pull a vector of x, y, etc. from a vector of points
        // ----------------------------------------------------------------------
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

        // ----------------------------------------------------------------------
        //! Getters
        // ----------------------------------------------------------------------
        std::string        GetName()   const {return m_name;}
        std::vector<Point> GetPoints() const {return m_points;}

        // ----------------------------------------------------------------------
        //! Setters
        // ----------------------------------------------------------------------
        void SetName(const std::string& name)            {m_name = name;}
        void SetPoints(const std::vector<Point>& points) {m_points = points;}

        // ----------------------------------------------------------------------
        //! Reset points
        // ----------------------------------------------------------------------
        void ResetPoints() {

          m_points.clear();
          return;

        }  // end 'ResetPoints()'

        // ----------------------------------------------------------------------
        //! Add a point
        // ----------------------------------------------------------------------
        void AddPoint(const Point& point) {

          m_points.push_back(point);
          return;

        }  // end 'AddPoint(Point&)'

        // ----------------------------------------------------------------------
        //! Make a TGraph
        // ----------------------------------------------------------------------
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

        // ----------------------------------------------------------------------
        //! Make a TGraphErrors
        // ----------------------------------------------------------------------
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

        // ----------------------------------------------------------------------
        //! Make a TGraphAsymmErrors
        // ----------------------------------------------------------------------
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

        // ----------------------------------------------------------------------
        //! default ctor/dtor
        // ----------------------------------------------------------------------
        Definition()  {};
        ~Definition() {};

        // ----------------------------------------------------------------------
        //! ctor accepting a name
        // ----------------------------------------------------------------------
        Definition(const std::string& name) {

          SetName(name);

        }  // end ctor(std::string)

    };  // end Definition

  }  // end GraphHelper namespace
}  // end ROOTAnalysisUtilities namespace


#endif

// end ========================================================================
