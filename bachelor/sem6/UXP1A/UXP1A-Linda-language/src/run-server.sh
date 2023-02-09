CMAKE_DICT=../cmake-build-debug
SERVER=linda-server

make --silent --directory=$CMAKE_DICT $SERVER

$CMAKE_DICT/$SERVER