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

#include "Teuchos_RCP.hpp"
#include "tadiga_IGES_geometry.h"

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
