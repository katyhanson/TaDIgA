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
#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"

#include "Teuchos_RCP.hpp"

#include "tadiga_IGES_geometry.h"

tadiga::IgesGeometry::IgesGeometry(
    const Teuchos::RCP<const Teuchos::Comm<int>>& kComm,
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : kComm_(kComm) {
    const auto kFileName = kGeometryParameters->get<std::string>("File Name");

    const auto kIgesReader = Teuchos::rcp(new IGESControl_Reader);
    const auto status = kIgesReader->ReadFile(kFileName.c_str());

    // TODO(johntfoster@gmail.com): Check the status of the file
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
};
