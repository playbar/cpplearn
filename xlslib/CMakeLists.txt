include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(xlslib STATIC
        src/xlslib/assert_assist.cpp
        src/xlslib/blank.cpp
        src/xlslib/boolean.cpp
        src/xlslib/cbridge.cpp
        src/xlslib/cell.cpp
        src/xlslib/colinfo.cpp
        src/xlslib/colors.cpp
        src/xlslib/continue.cpp
        src/xlslib/datast.cpp
        src/xlslib/docsumminfo.cpp
        src/xlslib/err.cpp
        src/xlslib/extformat.cpp
        src/xlslib/font.cpp
        src/xlslib/format.cpp
        src/xlslib/formula.cpp
        src/xlslib/formula_cell.cpp
        src/xlslib/formula_estimate.cpp
        src/xlslib/formula_expr.cpp
        src/xlslib/globalrec.cpp
        src/xlslib/HPSF.cpp
        src/xlslib/index.cpp
        src/xlslib/label.cpp
        src/xlslib/merged.cpp
        src/xlslib/note.cpp
        src/xlslib/number.cpp
        src/xlslib/range.cpp
        src/xlslib/recdef.cpp
        src/xlslib/record.cpp
        src/xlslib/row.cpp
        src/xlslib/sheetrec.cpp
        src/xlslib/summinfo.cpp
        src/xlslib/unit.cpp
        src/xlslib/workbook.cpp
        src/oledoc/binfile.cpp
        src/oledoc/oledoc.cpp
        src/oledoc/olefs.cpp
        src/oledoc/oleprop.cpp)


add_executable(mainCPP
        targets/mainCPP.cpp
        targets/md5.c
        targets/md5cpp.cpp)
target_link_libraries(mainCPP xlslib)


add_executable(writexls
        writexls.cpp
        targets/md5.c
        targets/md5cpp.cpp)
target_link_libraries(writexls xlslib)

