export CMTPROJECTPATH=""
export JUNOTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-Pre2
export OEC_EF=/hpcfs/juno/junogpu/liuyan2016/cor-ana
export JUNO_OFFLINE_OFF=0

#export PATH="/junofs/users/liuyan2016/OEC/mpi/mpi-install/bin:"$PATH
#export LD_LIBRARY_PATH=/junofs/users/liuyan2016/OEC/mpi/mpi-install/lib:$LD_LIBRARY_PATH

export CMTPROJECTPATH=${OEC_EF}:${CMTPROJECTPATH}
pushd $JUNOTOP >& /dev/null
    source setup.sh
popd >& /dev/null

pushd $JUNOTOP/offline/Examples/Tutorial/cmt/ >& /dev/null
    source setup.sh
popd >& /dev/null

pushd $OEC_EF/cmt/ >& /dev/null
    source setup.sh
popd >& /dev/null

