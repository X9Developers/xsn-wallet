import qbs
import qbs.Utilities

CppApplication {
    Depends { name: "Qt.core" }
    Depends { name: "Qt.testlib" }
    Depends { name: "core" }
    Depends { name: "gtest" }
    name: "core_tests"
    type: base.concat("autotest")

    files: [ "main.cpp", "tst_coretests.hpp" ]

    Group {
        name: "testdata"
        prefix: "testdata/"
        files: ["**/*"]
        fileTags: []
    }
}
