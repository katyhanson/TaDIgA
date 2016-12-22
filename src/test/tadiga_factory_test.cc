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

#include <fstream>
#include <iostream>

#include "Teuchos_UnitTestHarness.hpp"
#include "Tpetra_DefaultPlatform.hpp"

#include "Teuchos_XMLParameterListCoreHelpers.hpp"
#include "Teuchos_YamlParser_decl.hpp"

#include "tadiga_factory.h"

namespace tadiga_test {

class TestSetup {
   public:
    TestSetup();

    Teuchos::RCP<const Teuchos::Comm<int>> kComm;

    Teuchos::RCP<Teuchos::ParameterList> parameters;

    std::string filename;
};

TestSetup::TestSetup() {
    kComm = Tpetra::DefaultPlatform::getDefaultPlatform().getComm();

    // Create temporary file
    // std::FILE* temp_file = std::tmpfile();

    // Get file name
    // const std::string filename = std::to_string(fileno(temp_file));

    // Create parameter list
    parameters = Teuchos::rcp(new Teuchos::ParameterList());

    parameters->set("Verbose", true);

    filename = "/Users/john/Desktop/write_test.yaml";

    Teuchos::YAMLParameterList::writeYamlFile(filename, parameters);
}

TEUCHOS_UNIT_TEST(Parser, Default) {
    const auto test_fixture = Teuchos::rcp(new TestSetup());

    // Create factory object to produce main tadiga object
    const auto parameters = tadiga::TadigaParser::parse(test_fixture->filename);

    // Retrieve
    const bool default_verbose_value = parameters->get<bool>("Verbose");

    TEST_EQUALITY(default_verbose_value, true)
}

TEUCHOS_UNIT_TEST(Parser, File) {
    const auto test_fixture = Teuchos::rcp(new TestSetup());

    // Write some raw yaml to the temp file
    std::string test_yaml =
        "ANONYMOUS:\n"
        "  Verbose: \"true\"\n"
        "...";
    std::ofstream temp_file("/Users/john/Desktop/test.yaml");
    // std::ofstream temp_file(test_fixture->filename);
    temp_file << test_yaml;
    temp_file.close();

    // Create factory object to produce main tadiga object
    // const auto parameters =
    // tadiga::TadigaParser::parse(test_fixture->filename);
    const auto parameters =
        tadiga::TadigaParser::parse("/Users/john/Desktop/write_test.yaml");

    // Retrieve
    const bool default_verbose_value = parameters->get<bool>("Verbose");

    TEST_EQUALITY(default_verbose_value, true)
}
}
