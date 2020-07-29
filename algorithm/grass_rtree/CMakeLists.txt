add_executable(rtree_test1
        card.c
        ilist.c
        index.c
        indexf.c
        indexm.c
        io.c
        node.c
        rect.c
        split.c
        test_basics.c
        )

target_include_directories(rtree_test1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/
        )
