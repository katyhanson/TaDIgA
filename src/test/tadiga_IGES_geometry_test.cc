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
#include "Teuchos_YamlParser_decl.hpp"
#include "Tpetra_DefaultPlatform.hpp"

#include "tadiga_parser.h"

namespace tadiga_test {

class TestSetup {
   public:
    TestSetup() {}

    ~TestSetup() { fclose(temp_file_); };

    std::string GetYamlFileName() {
        return std::to_string(fileno(temp_yaml_file_));
    }
    std::string GetIgesFileName() {
        return std::to_string(fileno(temp_iges_file_));
    }

   private:
    // Get communicator from test runner
    Teuchos::RCP<const Teuchos::Comm<int>> kComm_ =
        Tpetra::DefaultPlatform::getDefaultPlatform().getComm()
        :

          // Create temporary file
          std::FILE* temp_yaml_file_ = std::tmpfile();
    std::FILE* temp_iges_file_ = std::tmpfile();
};

TEUCHOS_UNIT_TEST(IGES Geometry, Yaml Type) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::RCP(new Teuchos::ParameterList());

    // parameters.set("Geometry");
    parameters.set("Type", "IGES");
    parameters.set("File Name","test.igs";

    // write yaml file
    Teuchos::YAMLParameterList::writeYamlFile(kTestFixture->GetYamlFileName(),
                                              parameters);

    parameters = tadiga::TadigaParser::parse(kTestFixture->GetYamlFileName(), parameters);
    const auto yaml_type_value = parameters->get<auto>("Type");
    TEST_EQUALITY(Type, "IGES");
    
    // write iges file
    int writeiges() {
        ofstream igesfile;
        igesfile.open("test.igs");
        igesfile
            << "3D InterOp IGES (Version 21 0 1), Spatial Corp. Copyright (c) 1999-2007.S      1
            1H,
            , 1H;
        , 6HNoname, 8Htest.igs, 13HSpatial Corp., 20H3D InterOp ACIS / IGES, 32,
            G 1 38, 6, 308, 15, 6HNoname, 1.000, 2, 2HMM, 1, 1.000,
            15H20170129.212217, 1.0e-06, G 2 0.00, 6HNoname, 6HNoname, 11, 0,
            15H20170129.212217;
        G 3 110 1 0 0 0 0 0 000010001D 1 110 0 0 1 0 0 0 0D 2 122 2 0 0 0 0 0 000010001D 3 122 0 0 1 0 0 0 0D 4 110 3 0 0 0 0 0 000010001D 5 110 0 0 1 0 0 0 0D 6 110 4 0 0 0 0 0 000010001D 7 110 0 0 1 0 0 0 0D 8 110 5 0 0 0 0 0 000010001D 9 110 0 0 1 0 0 0 0D 10 110 6 0 0 0 0 0 000010001D 11 110 0 0 1 0 0 0 0D 12 102 7 0 0 0 0 0 000010001D 13 102 0 0 1 0 0 0 0D 14 142 8 0 0 0 0 0 000010001D 15 142 0 0 1 0 0 0 0D 16 144 9 0 0 0 0 0 000000001D 17 144 0 0 1 0 0 0 0D 18 110,
            -0.5, -0.5, 0., 0.5, -0.5, 0.;
        1P 1 122, 1, -0.5, 0.5, 0.;
        3P 2 110, 0.5, 0.5, 0., -0.5, 0.5, 0.;
        5P 3 110, -0.5, 0.5, 0., -0.5, -0.5, 0.;
        7P 4 110, -0.5, -0.5, 0., 0.5, -0.5, 0.;
        9P 5 110, 0.5, -0.5, 0., 0.5, 0.5, 0.;
        11P 6 102, 4, 5, 7, 9, 11;
        13P 7 142, 1, 3, 0, 13, 2;
        15P 8 144, 3, 1, 0, 15;
        17P 9 S 1G 3D 18P 9 T 1 ";
            igesfile.close();
        return 0;
    }
    // parse and run tadiga
}
