cmake_minimum_required(VERSION "3.26.4")

set(LIST_FILES "../include/cutil/list.h" "../source/list.c")
set(HASH_TABLE_FILES "../include/cutil/hashTable.h" "../source/hashTable.c")

add_executable(listTests list.c ${LIST_FILES})
add_test(NAME ListTests COMMAND listTests)

add_executable(hashTableTests hashTable.c ${HASH_TABLE_FILES} ${LIST_FILES})
add_test(NAME HashTableTests COMMAND hashTableTests)