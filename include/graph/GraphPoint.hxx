/// ===========================================================================
/*! \file   GraphPoint.hxx
 *  \author Derek Anderson
 *  \date   10.21.2024
 *
 *  Definition of a point of a graph.
 */
/// ===========================================================================

#ifndef RAU_GRAPHPOINT_HXX
#define RAU_GRAPHPOINT_HXX

// c++ utilities
#include <limits>
#include <utility>



namespace ROOTAnalysisUtilities {
  namespace Graph {

    // ========================================================================
    //! Point
    // ========================================================================
    /*! A small struct to consolidate data
     *  for a point on a graph
     */
    struct Point {

      // members
      double x     = std::numeric_limits<double>::max();
      double y     = std::numeric_limits<double>::max();
      double ex    = std::numeric_limits<double>::max();
      double ex_lo = std::numeric_limits<double>::max();
      double ex_hi = std::numeric_limits<double>::max();
      double ey    = std::numeric_limits<double>::max();
      double ey_lo = std::numeric_limits<double>::max();
      double ey_hi = std::numeric_limits<double>::max();

      // ----------------------------------------------------------------------
      //! default ctor/dtor
      // ----------------------------------------------------------------------
      Point()  {};
      ~Point() {};

      // ----------------------------------------------------------------------
      //! ctor without errors
      // ----------------------------------------------------------------------
      Point(const double x_arg, const double y_arg) {

        x = x_arg;
        y = y_arg;

      }  // end ctor(double, double)

      // ----------------------------------------------------------------------
      //! ctor accepting symmetric errors
      // ----------------------------------------------------------------------
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

      // ----------------------------------------------------------------------
      //! ctor accepting asymmetric errors
      // ----------------------------------------------------------------------
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


  }  // end Graph namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
