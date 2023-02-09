CMAKE_DICT=../cmake-build-debug

TEST_APP=linda-test
SERVER=linda-server

make --silent --directory=$CMAKE_DICT $TEST_APP


clear

$CMAKE_DICT/$TEST_APP $1