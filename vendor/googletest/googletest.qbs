import qbs

import "googlecommon.js" as googleCommon

Product {
    id: root
    name: "gtest"
    type: "staticlibrary"

    Depends { name: "cpp" }

    property string googletestDir: path + "/" + "googletest"
    property var includePaths: [].concat(googleCommon.getGTestIncludes(googletestDir))
    .concat(googleCommon.getGMockIncludes(googletestDir))

    cpp.includePaths: includePaths
    Properties {
        condition: qbs.targetOS.contains("macos")
        cpp.minimumMacosVersion: "10.9"
    }

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: root.includePaths
    }

    files: googleCommon.getGTestAll(googletestDir).concat(googleCommon.getGMockAll(googletestDir))
}
