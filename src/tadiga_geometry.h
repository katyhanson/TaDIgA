// Copyright 2015 John T. Foster

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef TADIGA_GEOMETRY_H
#define TADIGA_GEOMETRY_H
#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"
#include "TopoDS_Wire.hxx"
namespace tadiga {

class Geometry {
   public:
    Geometry(){};
    void LoadBalanceFaceList();

    auto GetNumberIges_Entities() { return number_of_iges_entities_; }
    auto GetNumberTransferred_Entities() {
        return number_of_transferred_entities_;
    }

   private:
    //! Private to prohibit copying.
    Geometry(const Geometry &);

    Geometry &operator=(const Geometry &);

   protected:
    int number_of_iges_entities_;
    int number_of_transferred_entities_;

    TopoDS_Shape transferred_OCCT_shape;
    TopoDS_Shape NURBS_converted_shape;
};
};

#endif  // TADIGA_GEOMETRY_H
