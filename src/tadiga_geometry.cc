// Copyright 2016-2017
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
#include "tadiga_geometry.h"
#include "BRepAdaptor_Curve.hxx"
#include "BRepAdaptor_Surface.hxx"
#include "BRepBuilderAPI_NurbsConvert.hxx"
#include "BRep_Tool.hxx"
#include "BSplCLib.hxx"
#include "Geom_BSplineCurve.hxx"
#include "Geom_BSplineSurface.hxx"
#include "NCollection_Array1.hxx"
#include "ShapeAnalysis_Edge.hxx"
#include "TColStd_Array1OfInteger.hxx"
#include "TColStd_Array1OfReal.hxx"
#include "Teuchos_RCP.hpp"
#include "TopExp_Explorer.hxx"
#include "bsplines.hpp"
#include "math_Matrix.hxx"
#include "tadiga_IGES_geometry.h"

tadiga::Geometry::Geometry(
    const Teuchos::RCP<const Teuchos::Comm<int>>& kComm,
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : kComm_(kComm){};

void tadiga::Geometry::initialize() {
    // Convert transferred OCCT Shapes to NURBS & retrieve
    const auto kNURBSConverter = Teuchos::rcp(new BRepBuilderAPI_NurbsConvert);
    kNURBSConverter->Perform(transferred_OCCT_shape_);
    TopoDS_Shape NURBS_converted_shape_ =
        kNURBSConverter->ModifiedShape(transferred_OCCT_shape_);

    int EdgeCounter = 1;
    // Look for ToopDS_Edges in  NURBS_converted_shape
    TopExp_Explorer ShapeExplorer;
    for (ShapeExplorer.Init(NURBS_converted_shape_, TopAbs_EDGE);
         ShapeExplorer.More(); ShapeExplorer.Next()) {
        const TopoDS_Edge& ExtractedEdge =
            TopoDS::Edge(ShapeExplorer.Current());
        const auto BRepAdaptorCurve =
            Teuchos::rcp(new BRepAdaptor_Curve(ExtractedEdge));
        Handle(Geom_BSplineCurve) ExtractedBsplineCurve =
            BRepAdaptorCurve->BSpline();
        int number_of_knots_ = ExtractedBsplineCurve->NbKnots();
        TColStd_Array1OfReal knot_sequence_ =
            ExtractedBsplineCurve->Knots();  // Returns "flat knots", no
                                             // repeated knot multiplicities
        length_ = knot_sequence_.Length();
        std::cout << "Knot Sequence Length: " << length_ << endl;

        TColgp_Array1OfPnt bspline_poles_ = ExtractedBsplineCurve->Poles();
        TColStd_Array1OfInteger multiplicities_ =
            ExtractedBsplineCurve->Multiplicities();

        // Print TColStd_Array1OfReal knot vector to integer array
        std::cout << "EDGE #" << EdgeCounter << endl;
        std::cout << "Knot Sequence:";
        for (int i = 1; i <= length_; i++) {
            std::cout << " " << knot_sequence_.Value(i);
            knot_sequence_int_[i - 1] = knot_sequence_.Value(i);
        }
        std::cout << endl;

        // EVALUATE BSPLINES FOR EDGES
        int knotsLen = BSplCLib::KnotsLength(knot_sequence_);
        TColStd_Array1OfReal knots(1, knotsLen);
        TColStd_Array1OfInteger mults(1, knotsLen);
        BSplCLib::Knots(knot_sequence_, knots,
                        mults);  // Creates flat knot sequence

        if (BSplCLib::KnotForm(knots, 1, knotsLen) == BSplCLib_Uniform) {
            std::cout << "Knots uniform" << endl;
        } else {
            std::cout << "Knots non-uniform" << endl;
        }

        const double x = 1;  // Evaluation Parameter
        int Iloc = 0;
        BSplCLib::Hunt(knot_sequence_, x, Iloc);
        // Finds knot span location of evaluation parameter
        std::cout << "Iloc: " << Iloc << endl;
        int k = 0;  // Derivative Order
        int p = 1;  // Degree
        int order = p + 1;
        int FirstNonZeroIndex = 0;
        math_Matrix BsplineBasis(1, 1, 1, order, 0);  // Stores results
        // Evaluation function
        BSplCLib::EvalBsplineBasis(1, k, order, knot_sequence_, x,
                                   FirstNonZeroIndex, BsplineBasis);
        std::cout << "Bspline Evalutation: " << BsplineBasis << endl;

        EdgeCounter++;
    }

    // Look for TopoDS_Faces in NURBS_converted_shape
    int FaceCounter = 1;
    for (ShapeExplorer.Init(NURBS_converted_shape_, TopAbs_FACE);
         ShapeExplorer.More(); ShapeExplorer.Next()) {
        const TopoDS_Face& ExtractedFace =
            TopoDS::Face(ShapeExplorer.Current());
        const auto BRepAdaptorSurface =
            Teuchos::rcp(new BRepAdaptor_Surface(ExtractedFace));
        Handle(Geom_BSplineSurface) ExtractedBSplineSurface =
            BRepAdaptorSurface->BSpline();
        std::cout << "FACE #" << FaceCounter << endl;
        TColStd_Array1OfReal U_knot_sequence_ =
            ExtractedBSplineSurface->UKnotSequence();
        Ulength_ = U_knot_sequence_.Length();
        std::cout << "U Knot Sequence Length: " << Ulength_ << endl;
        std::cout << " U Knot Sequence:";
        for (int i = 1; i <= Ulength_; i++) {
            std::cout << " " << U_knot_sequence_.Value(i);
            U_knot_sequence_int_[i - 1] = U_knot_sequence_.Value(i);
        }
        std::cout << endl;

        TColStd_Array1OfReal V_knot_sequence_ =
            ExtractedBSplineSurface->VKnotSequence();
        Vlength_ = V_knot_sequence_.Length();
        std::cout << "V Knot Sequence Length: " << Vlength_ << endl;
        std::cout << " V Knot Sequence:";
        for (int i = 1; i <= Vlength_; i++) {
            std::cout << " " << V_knot_sequence_.Value(i);
            V_knot_sequence_int_[i - 1] = V_knot_sequence_.Value(i);
        }
        std::cout << endl;
        FaceCounter++;
    }
};
