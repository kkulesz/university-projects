FILE_NAME='file'

#source file names
CPP_FILE="${FILE_NAME}.cpp"
PYTHON_FILE="${FILE_NAME}.py"

#output files
PYTHON_OUTPUT=py_output.txt
CPP_OUTPUT=cpp_output.txt

#compile cpp
EXEC_CPP_FILE='cpp.exec'
g++ $CPP_FILE -o $EXEC_CPP_FILE

#get output of sources
python $PYTHON_FILE > $PYTHON_OUTPUT
./$EXEC_CPP_FILE > $CPP_OUTPUT

#check if files are the same
if cmp -s "$PYTHON_OUTPUT" "$CPP_OUTPUT"; then
  echo "OK - files are the same"
else
  echo "ERROR - files are NOT the same"
fi

#tidy up
# remove exec
rm -d $EXEC_CPP_FILE
#remove outputs
rm -d $CPP_OUTPUT $PYTHON_OUTPUT