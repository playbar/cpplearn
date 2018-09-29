set(SOURCE_PARSESO  sqlite3.c stmttest.cpp)
add_executable(sqlitetest ${SOURCE_PARSESO})

set(SOURCE_SHELL  sqlite3.c shell.c)
add_executable(sqlite3 ${SOURCE_SHELL})