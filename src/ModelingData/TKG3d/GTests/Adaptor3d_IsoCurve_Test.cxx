// Copyright (c) 2026 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <gtest/gtest.h>

#include <Adaptor3d_IsoCurve.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <Precision.hxx>
#include <gp_Ax3.hxx>
#include <gp_Dir.hxx>
#include <gp_Pnt.hxx>

#include <cmath>

//=================================================================================================

TEST(Adaptor3d_IsoCurveTest, LoadIsoVFullUPeriodWithParametricRoundoffPreservesFullPeriod)
{
  const double aRadius        = 250.0;
  const double aUFirst        = 0.98620381059140827;
  const double aPeriod        = 2.0 * M_PI;
  const double aBoundRoundoff = 0.75 * Precision::PConfusion();

  occ::handle<Geom_CylindricalSurface> aCylinder =
    new Geom_CylindricalSurface(gp_Ax3(gp_Pnt(0.0, 0.0, 0.0), gp_Dir(0.0, 0.0, 1.0)), aRadius);
  occ::handle<GeomAdaptor_Surface> aGeomSurface =
    new GeomAdaptor_Surface(aCylinder, aUFirst, aUFirst + aPeriod + aBoundRoundoff, -1.0, 1.0);
  occ::handle<Adaptor3d_Surface> anAdaptor(aGeomSurface);

  Adaptor3d_IsoCurve anIsoCurve(anAdaptor, GeomAbs_IsoV, 0.0);

  EXPECT_NEAR(anIsoCurve.FirstParameter(), aUFirst, Precision::PConfusion());
  EXPECT_NEAR(anIsoCurve.LastParameter(), aUFirst + aPeriod, Precision::PConfusion());
  EXPECT_NEAR(anIsoCurve.LastParameter() - anIsoCurve.FirstParameter(),
              aPeriod,
              Precision::PConfusion());
}
