
export EACC_ROOT=`pwd`

echo "Exporting the current path: $EACC_ROOT"

export LD_LIBRARY_PATH=$EACC_ROOT/3rdparty/lib:$EACC_ROOT/3rdparty/mysql/lib:$EACC_ROOT/3rdparty/mysql-connector-c++-1.1.0/driver/:$LD_LIBRARY_PATH
export PATH=$EACC_ROOT/3rdparty/bin:$EACC_ROOT/3rdparty/mysql/bin:$PATH

