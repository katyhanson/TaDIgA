// Copyright 2016-2017 John T. Foster, Katy L. Hanson

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
<<<<<<< HEAD
=======
#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"

#include "Teuchos_RCP.hpp"

>>>>>>> iges
#include "tadiga_IGES_geometry.h"
#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "Teuchos_RCP.hpp"
#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"

#include "BRepAdaptor_Curve.hxx"
#include "BRepAdaptor_Surface.hxx"
#include "BRepBuilderAPI_NurbsConvert.hxx"
#include "BRep_Tool.hxx"
#include "BSplCLib.hxx"
#include "Geom_BSplineCurve.hxx"
#include "Geom_BSplineSurface.hxx"
#include "NCollection_Array1.hxx"
#include "NCollection_List.hxx"
#include "ShapeAnalysis_Edge.hxx"
#include "Standard_Real.hxx"
#include "TopExp_Explorer.hxx"

tadiga::IgesGeometry::IgesGeometry(
    const Teuchos::RCP<const Teuchos::Comm<int>>& kComm,
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : kComm_(kComm) {
    const auto kFileName = kGeometryParameters->get<std::string>("File Name");

    const auto kIgesReader = Teuchos::rcp(new IGESControl_Reader);
    const auto status = kIgesReader->ReadFile(kFileName.c_str());

    // TODO(johntfoster@gmail.com): Check the status of the file
<<<<<<< HEAD

    // Returns list of all ntities from IGES file
    Handle(TColStd_HSequenceOfTransient) igesEntityList =
        kIgesReader->GiveList();
    // Transfer all entities at once
    number_of_iges_entities_ = igesEntityList->Length();
    number_of_transferred_entities_ = kIgesReader->TransferList(igesEntityList);

    // Obtain result in a single OCCT shape
    TopoDS_Shape transferred_OCCT_shape = kIgesReader->OneShape();

    // Convert transferred OCCT Shapes to NURBS
    const auto kNURBSConverter = Teuchos::rcp(new BRepBuilderAPI_NurbsConvert);
    kNURBSConverter->Perform(transferred_OCCT_shape);

    // Retrieve modified NURBS converted transferred_OCCT_shape
    TopoDS_Shape NURBS_converted_shape =
        kNURBSConverter->ModifiedShape(transferred_OCCT_shape);

    // Look for ToopDS_Edges in  NURBS_converted_shape
    TopExp_Explorer ShapeExplorer;
    for (ShapeExplorer.Init(NURBS_converted_shape, TopAbs_EDGE);
         ShapeExplorer.More(); ShapeExplorer.Next()) {
        // Convert found to type  TopoDS_Edge
        const TopoDS_Edge& ExtractedEdge =
            TopoDS::Edge(ShapeExplorer.Current());
        // Create Adaptor BRep Curve to Read Geometry of Extracted TopoDS_Edge
        const auto BRepAdaptorCurve =
            Teuchos::rcp(new BRepAdaptor_Curve(ExtractedEdge));
        // Use Adaptor BRep Curve to Read BSpline
        Handle(Geom_BSplineCurve) ExtractedBSplineCurve =
            BRepAdaptorCurve->BSpline();
        // Extract Knot Sequence from BSpline Extracted with the Explorer from
        // the NURBS_converted_shape
        TColStd_Array1OfReal knot_sequence = ExtractedBSplineCurve->Knots();
    }

    // Look for TopoDS_Faces in NURBS_converted_shape
    for (ShapeExplorer.Init(NURBS_converted_shape, TopAbs_FACE);
         ShapeExplorer.More(); ShapeExplorer.Next()) {
        // Convert found to type  TopoDS_Face
        const TopoDS_Face& ExtractedFace =
            TopoDS::Face(ShapeExplorer.Current());
        // Create Adaptor BRep Curve to Read Geometry of Extracted
        // TopoDS_Face
        const auto BRepAdaptorSurface =
            Teuchos::rcp(new BRepAdaptor_Surface(ExtractedFace));
        // Use Adaptor BRep Suface to Read BSplineSurface
        Handle(Geom_BSplineSurface) ExtractedBSplineSurface =
            BRepAdaptorSurface->BSpline();
        // Extract Knot Sequence (U and V surface dimensions) from BSpline
        // Extracted from
        // NURBS_converted_shape
        TColStd_Array1OfReal U_knot_sequence =
            ExtractedBSplineSurface->UKnotSequence();
        TColStd_Array1OfReal V_knot_sequence =
            ExtractedBSplineSurface->VKnotSequence();
    }
=======
    // selects all IGES faces in the file and puts them into a list  called
    // MyList; Returns list of entities from IGES file

    Handle(TColStd_HSequenceOfTransient) myFaceList =
        kIgesReader->GiveList("iges-faces");
    Handle(TColStd_HSequenceOfTransient) myLineList =
        kIgesReader->GiveList("iges-type(110)");
    Handle(TColStd_HSequenceOfTransient) myTabulatedCylinderList =
        kIgesReader->GiveList("iges-type(122)");
    Handle(TColStd_HSequenceOfTransient) myCompositeCurveList =
        kIgesReader->GiveList("iges-type(102)");
    Handle(TColStd_HSequenceOfTransient) myCurveOnSurfaceList =
        kIgesReader->GiveList("iges-type(142)");
    Handle(TColStd_HSequenceOfTransient) myBSplineCurveList =
        kIgesReader->GiveList("iges-type(126)");

    number_of_iges_face_ = myFaceList->Length();
    number_of_transferred_face_ = kIgesReader->TransferList(myFaceList);

    number_of_iges_line_ = myLineList->Length();
    number_of_transferred_line_ = kIgesReader->TransferList(myLineList);

    number_of_iges_tabulated_cylinder_ = myTabulatedCylinderList->Length();
    number_of_transferred_tabulated_cylinder_ =
        kIgesReader->TransferList(myTabulatedCylinderList);

    number_of_iges_composite_curve_ = myCompositeCurveList->Length();
    number_of_transferred_composite_curve_ =
        kIgesReader->TransferList(myCompositeCurveList);

    number_of_iges_curve_on_surface_ = myCurveOnSurfaceList->Length();
    number_of_transferred_curve_on_surface_ =
        kIgesReader->TransferList(myCurveOnSurfaceList);

    TopoDS_Shape transfered_OCCT_shape = kIgesReader->OneShape();
    // Obtains the results in a single OCCT shape
>>>>>>> iges
};
