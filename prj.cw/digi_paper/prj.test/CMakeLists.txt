add_executable(digi_paper.test digi_paper.test.cpp "digi_paper.test.cpp")
target_link_libraries(digi_paper.test digiPaper)
add_test(NAME digi_paper.test COMMAND digi_paper.test)



install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../tests DESTINATION .)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../doc_doxygen DESTINATION ./bin.rel)