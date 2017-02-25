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
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
namespace tadiga {

class Geometry {
   public:
    Geometry(){};

    void LoadBalanceFaceList();

    auto GetNumberFaces() { return nb_face_; }
    auto SetNumberFaces(int number_of_face) {
        nb_face_ = number_of_face;
        return;
    }
    auto GetNumberLines() { return nb_line_; }
    auto SetNumberLines(int number_of_line) {
        nb_line_ = number_of_line;
        return;
    }
    auto GetNumberTabCylinders() { return nb_tab_cylinder_; }
    auto SetNumberTabCylinders(int number_of_tab_cylinder) {
        nb_tab_cylinder_ = number_of_tab_cylinder;
        return;
    }
    auto GetNumberCompositeCurves() { return nb_composite_curve_; }
    auto SetNumberCompositeCurves(int number_of_composite_curve) {
        nb_composite_curve_ = number_of_composite_curve;
        return;
    }
    auto GetNumberCurveOnSurface() { return nb_curve_on_surface_; }
    auto SetNumberCurveOnSurface(int number_of_curve_on_surface) {
        nb_curve_on_surface_ = number_of_curve_on_surface;
        return;
    }

   private:
    //! Private to prohibit copying.
    Geometry(const Geometry &);

    Geometry &operator=(const Geometry &);

    int nb_face_;
    int nb_line_;
    int nb_tab_cylinder_;
    int nb_composite_curve_;
    int nb_curve_on_surface_;
    int nb_point_;
    int nb_bspline_curve_;

    TopoDS_Edge line_;
    TopoDS_Face face_;
    TopoDS_Face tab_cylinder_;
    TopoDS_Wire composite_curve_;
    TopoDS_Wire curve_on_surface_;
};
}

#endif  // TADIGA_GEOMETRY_H
