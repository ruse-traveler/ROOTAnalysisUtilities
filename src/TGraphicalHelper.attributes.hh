// ----------------------------------------------------------------------------
// 'TGraphicalHelper.attributes.hh'
// Derek Anderson
// 01.11.2022
//
// A class to streamline interacting
// with graphical objects (e.g.
// histograms) in ROOT
// ----------------------------------------------------------------------------

#pragma once

#include "TGraphicalHelper.hh"



// attribute style setters ----------------------------------------------------

template <typename Type> void TGraphicalHelper::set_marker_style(Type *to_be_styled, const TMarkerStyle style) {

  to_be_styled -> SetMarkerColorAlpha(style.marker_color, style.marker_alpha);
  to_be_styled -> SetMarkerStyle(style.marker_style);
  to_be_styled -> SetMarkerSize(style.marker_size);
  return;

}  // end 'set_marker_style(auto &, TMarkerStyle)'



template <typename Type> void TGraphicalHelper::set_line_style(Type *to_be_styled, const TLineStyle style) {

  to_be_styled -> setLineColorAlpha(style.line_color, style.line_alpha);
  to_be_styled -> SetLineStyle(style.line_style);
  to_be_styled -> SetLineWidth(style.line_width);
  return;

}  // end 'set_line_style(auto &, TLineStyle)'



template <typename Type> void TGraphicalHelper::set_fill_style(Type *to_be_styled, const TFillStyle style) {

  to_be_styled -> SetFillColorAlpha(style.fill_color, style.fill_alpha);
  to_be_styled -> SetFillStyle(style.fill_style);
  return;

}  // end 'set_fill_style(auto &, TFillStyle)'



template <typename Type> void TGraphicalHelper::set_axis_style(Type *to_be_styled, const TAxisStyle style, const Axis axis) {

  switch (TGraphicalHelper::axis) {
    case x:
      to_be_styled -> GetXaxis() -> CenterTitle(style.title_center);
      to_be_styled -> GetXaxis() -> SetTitleFont(style.title_font);
      to_be_styled -> GetXaxis() -> SetLabelFont(style.label_font);
      to_be_styled -> GetXaxis() -> SetTitleSize(style.title_size);
      to_be_styled -> GetXaxis() -> SetLabelSize(style.label_size);
      to_be_styled -> GetXaxis() -> SetTitleOffset(style.title_offset);
      to_be_styled -> GetXaxis() -> SetLabelOffset(style.label_offset);
      to_be_styled -> GetXaxis() -> SetTitle(style.axis_title.Data());
      break;
    case y:
      to_be_styled -> GetYaxis() -> CenterTitle(style.title_center);
      to_be_styled -> GetYaxis() -> SetTitleFont(style.title_font);
      to_be_styled -> GetYaxis() -> SetLabelFont(style.label_font);
      to_be_styled -> GetYaxis() -> SetTitleSize(style.title_size);
      to_be_styled -> GetYaxis() -> SetLabelSize(style.label_size);
      to_be_styled -> GetYaxis() -> SetTitleOffset(style.title_offset);
      to_be_styled -> GetYaxis() -> SetLabelOffset(style.label_offset);
      to_be_styled -> GetYaxis() -> SetTitle(style.axis_title.Data());
      break;
    case z:
      to_be_styled -> GetZaxis() -> CenterTitle(style.title_center);
      to_be_styled -> GetZaxis() -> SetTitleFont(style.title_font);
      to_be_styled -> GetZaxis() -> SetLabelFont(style.label_font);
      to_be_styled -> GetZaxis() -> SetTitleSize(style.title_size);
      to_be_styled -> GetZaxis() -> SetLabelSize(style.label_size);
      to_be_styled -> GetZaxis() -> SetTitleOffset(style.title_offset);
      to_be_styled -> GetZaxis() -> SetLabelOffset(style.label_offset);
      to_be_styled -> GetZaxis() -> SetTitle(style.axis_title.Data());
      break;
  }
  return;

}  // end 'set_axis_style(auto &, TAxisStyle)'

// end ------------------------------------------------------------------------

