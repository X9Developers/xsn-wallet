import qbs
import qbs.Utilities

CppApplication {
    Depends { name: "Qt.core" }
    Depends { name: "Qt.testlib" }
    Depends { name: "core" }
    Depends { name: "libbitcoin" }
    Depends { name: "gtest" }
    Depends { name: "bitcoin" }
    name: "core_tests"
    type: base.concat("autotest")

    files: [
        "main.cpp",
        "tst_addressmanager.hpp",
        "tst_coretests.hpp",
        "tst_keystorage.hpp",
    ]

    Group {
        name: "testdata"
        prefix: "testdata/"
        files: ["**/*"]
        fileTags: []
    }
}
