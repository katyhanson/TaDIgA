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
#include "tadiga_IGES_geometry.h"
#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "Teuchos_RCP.hpp"
#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"

tadiga::IgesGeometry::IgesGeometry(
    const Teuchos::RCP<const Teuchos::Comm<int>>& kComm,
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : kComm_(kComm) {
    const auto kFileName = kGeometryParameters->get<std::string>("File Name");

    const auto kIgesReader = Teuchos::rcp(new IGESControl_Reader);
    const auto status = kIgesReader->ReadFile(kFileName.c_str());

    // TODO(johntfoster@gmail.com): Check the status of the file
    // Returns list of all ntities from IGES file
    Handle(TColStd_HSequenceOfTransient) igesEntityList =
        kIgesReader->GiveList();
    // Transfer all entities at once
    number_of_iges_entities_ = igesEntityList->Length();
    number_of_transferred_entities_ = kIgesReader->TransferList(igesEntityList);

    // Obtain result in a single OCCT shape
    TopoDS_Shape transferred_OCCT_shape = kIgesReader->OneShape();
};
