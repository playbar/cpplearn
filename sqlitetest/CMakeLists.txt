set(SOURCE_SQLITE  sqlite3.c stmttest.cpp)
add_executable(sqlitetest ${SOURCE_SQLITE})

set(SOURCE_SHELL  sqlite3.c shell.c)
add_executable(sqlite3 ${SOURCE_SHELL})