dune_python_add_test(NAME pythontests
                     SCRIPT pythontests.py
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     LABELS quick)

dune_add_test(SOURCES test_embed1.cc
              LINK_LIBRARIES ${DUNE_LIBS} ${Python3_LIBRARIES}
              LABELS quick
              )

add_executable(test_embed2 EXCLUDE_FROM_ALL test_embed2.cc)
target_link_libraries(test_embed2 PUBLIC ${DUNE_LIBS} ${Python3_LIBRARIES})
# the following should apparently work but doesn't target_link_libraries(test_embed2 PRIVATE Python3::Python)
