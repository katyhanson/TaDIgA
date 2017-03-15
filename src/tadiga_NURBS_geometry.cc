// Copyright 2016-2017 John T. Foster, Katy L. Hanson
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
#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"

#include "Teuchos_RCP.hpp"
#include "tadiga_IGES_geometry.h"

#include "BRepAdaptor_Curve.hxx"
#include "BRepBuilderAPI_NurbsConvert.hxx"
#include "Geom_BSplineCurve.hxx"
#include "NCollection_Array1.hxx"
#include "NCollection_List.hxx"
#include "ShapeAnalysi_Edge.hxx"
#include "Standard_Real.hxx"
#include "TopExp_Explorer.hxx"

tadiga::Geometry::Geometry() {
    // Convert transferred OCCT Shapes to NURBS
    const auto kNURBSConverter = Teuchos::rcp(new BRepBuilderAPI_NurbsConvert);
    kNURBSConverter->Perform(transferred_OCCT_shape);

    // Retrieve modified NURBS converted transferred_OCCT_shape
    TopoDS_Shape NURBS_converted_shape =
        kNURBSConverter->ModifiedShape(transferred_OCCT_shap);

    // Extract Knot Sequence from NURBS converted shape using class
    // Geom_BSplineCurve
    TopExp_Explorer ShapeExplorer;
    for (ShapeExplorer.Init(NURBS_converted_shape, TopAbs_EDGE);
         ShapeExplorer.More(); ShapeExplorer.Next()) {
        // Convert found to type TopoDS_Edge
        const TopoDS_Edge& ExtractedEdge =
            TopoDS::Edge(ShapeExplorer.Current());
        // Create adaptor BRep curve to read geometry of extracted TopoDS_Edge
        const auto BRepAdaptor =
            Teuchos::rcp(new BRepAdaptor_Curve(ExtractedEdge));
        // Use adaptor BRep curve to read BSpline
        Handle(Geom_BSplineCurve) ExtractedBSpline = BRepAdaptor->BSpline();
        // Extract knot sequence from BSpline extracted from
        // NURBS_converted_shape
        TColStd_Array1OfReal knot_sequence = ExtractedEdgeSpline->Knots();
    }
};
