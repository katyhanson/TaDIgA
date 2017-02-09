// Copyrightse see notebook paper.  2017 John T. Foster, Katy L. Hanson

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <fstream>
#include <iostream>

#include "Teuchos_UnitTestHarness.hpp"
#include "Tpetra_DefaultPlatform.hpp"

#include "Teuchos_YamlParser_decl.hpp"

#include "tadiga_parser.h"

namespace tadiga_test {

class TestSetup {
   public:
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
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"

#include "Teuchos_RCP.hpp"

#include "tadiga_IGES_geometry.h"

    tadiga::IgesGeometry::IgesGeometry(
