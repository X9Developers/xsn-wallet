import qbs
import qbs.Utilities

CppApplication {
    id: test
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
        qbs.install: true
        files: ["**/*", "../../../app/assets/assets_conf.json"]
        fileTags: []
    }

    Group {     // Properties for the produced executable
        name: "tests"
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
