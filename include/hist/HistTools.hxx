/// ===========================================================================
/*! \file   HistTools.hxx
 *  \author Derek Anderson
 *  \date   10.24.2024
 *
 *  Useful tools related to histograms.
 */
/// ===========================================================================

#ifndef RAU_HISTTOOLS_HXX
#define RAU_HISTTOOLS_HXX

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
// rau componenets
#include "../graph/GraphPoint.hxx"



namespace ROOTAnalysisUtilities {
  namespace Tools {

    // ------------------------------------------------------------------------
    //! Different axes of histograms & graphs
    // ------------------------------------------------------------------------
    /*! FIXME this might be better served in a dedicated "Type" or "Constant"
     *  namespace...
     */ 
    enum class Axis {X, Y, Z};



    // ------------------------------------------------------------------------
    //! Wrapper function for std::pow
    // ------------------------------------------------------------------------
    double Exponentiate(const double arg, const double base = TMath::E()) {

      return std::pow(base, arg);

    }  // end 'Exponentiate(double)'



    // ------------------------------------------------------------------------
    //! Wrapper function for std::log
    // ------------------------------------------------------------------------
    double Log(const double arg, const double base = TMath::E()) {

      return std::log(arg) / std::log(base);

    }  // end 'Log(double, double)'



    // ------------------------------------------------------------------------
    //! Helper method to divide a range into a certain number of bins
    // ------------------------------------------------------------------------
    std::vector<double> GetBinEdges(
      const uint32_t num,
      const double start,
      const double stop
    ) {

      // throw error if start/stop are out of order
      // or if num is zero
      if (num <= 0)     assert(num > 0);
      if (start > stop) assert(start <= stop);

      // set start/stop, calculate bin steps
      const double step = (stop - start) / num;
 
      // instantiate vector to hold bins
      std::vector<double> bins;

      // and fill vector
      double edge = start;
      for (std::size_t inum = 0; inum < num; ++inum) {
        bins.push_back( edge );
        edge += step;
      }
      bins.push_back( edge );
      return bins;

    }  // end 'GetBinEdges(uint32_t, double, double)'



    // ------------------------------------------------------------------------
    //! Helper method to divide a range into a certain number of log bins
    // ------------------------------------------------------------------------
    std::vector<double> GetBinEdgesLog(
      const uint32_t num,
      const double start,
      const double stop,
      const double base = TMath::E()
    ) { 

      // throw error if start/stop are out of order
      // or if num is zero
      if (num <= 0)     assert(num > 0);
      if (start > stop) assert(start <= stop);

      // divide range in log space
      std::vector<double> bins = GetBinEdges(num, Log(start), Log(stop));

      // transform back from log & return
      std::transform(
        bins.begin(),
        bins.end(),
        bins.begin(),
        [&base](const double arg) {
          return Exponentiate(arg, base);
        }
      ); 
      return bins;

    }  // end 'GetBinEdgesLog(uint32_t, double, double, double)'



    // ------------------------------------------------------------------------
    //! Helper method to extract bin edges from a vector of RAU::Graph::Point
    // ------------------------------------------------------------------------
    std::vector<double> GetBinsFromPoints(
      const std::vector<Graph::Point>& points,
      const Axis axis = Axis::X
    ) {

      // instantiate vector to hold bin edges
      std::vector<double> bins;

      // grab all low edges
      for (const Graph::Point& point : points) {
        switch (axis) {
          case Axis::X:
            bins.push_back(point.x - point.ex_lo);
            break;
          case Axis::Y:
            bins.push_back(point.y - point.ey_lo);
            break;
          case Axis::Z:
            bins.push_back(point.z - point.ez_lo);
            break;
        }
      }

      // grab high edge of last bin & return
      switch (axis) {
        case Axis::X:
          bins.push_back(points.back().x + points.back().ex_hi);
          break;
        case Axis::Y:
          bins.push_back(points.back().y + points.back().ey_hi);
          break;
        case Axis::Z:
          bins.push_back(points.back().z + points.back().ez_hi);
          break;
      }
      return bins;

    }  // end 'GetBinsFromPoints(std::vector<Graph::Point>&)'



    // ------------------------------------------------------------------------
    //! Helper method to decompose a TH1 into a RAU::Graph::Point vector
    // ------------------------------------------------------------------------
    std::vector<Graph::Point> GetHistPoints(TH1* hist) {

      std::vector<Graph::Point> points;
      for (std::size_t ibin = 1; ibin <= hist -> GetNbinsX(); ++ibin) {
        points.emplace_back(
          hist -> GetBinCenter(ibin),
          hist -> GetBinContent(ibin),
          hist -> GetBinWidth(ibin),
          hist -> GetBinError(ibin)
        );
      }
      return points;

    }  // end 'GetHistPoints(TH1*)'



    // ------------------------------------------------------------------------
    //! Helper method to decompose a TH2 into a RAU::Graph::Point vector
    // ------------------------------------------------------------------------
    std::vector<Graph::Point> GetHistPoints(TH2* hist) {

      std::vector<Graph::Point> points;
      for (std::size_t ibinx = 1; ibinx <= hist -> GetNbinsX(); ++ibinx) {
        for (std::size_t ibiny = 1; ibiny <= hist -> GetNbinsY(); ++ibiny) {
          points.emplace_back(
            hist -> GetXaxis() -> GetBinCenter(ibinx),
            hist -> GetYaxis() -> GetBinCenter(ibiny),
            hist -> GetBinContent(ibinx, ibiny),
            hist -> GetXaxis() -> GetBinWidth(ibinx),
            hist -> GetYaxis() -> GetBinWidth(ibiny),
            hist -> GetBinError(ibinx, ibiny)
          );
        }
      }
      return points;

    }  // end 'GetHistPoints(TH2*)'

  }  // end Tools namespace
}  // end ROOTAnalysisUtilities namespace

#endif

// end ========================================================================
