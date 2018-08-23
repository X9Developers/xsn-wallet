import qbs

Project {
    name: "tests"

    SubProject {
        filePath: "core_tests/core_tests.qbs"
    }

    SubProject {
        filePath: parent.sourceDirectory + "/vendor/googletest/googletest.qbs"
    }
}
