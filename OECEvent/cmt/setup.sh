# echo "setup OECEvent v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtOECEventtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtOECEventtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=OECEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana  -no_cleanup $* >${cmtOECEventtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=OECEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana  -no_cleanup $* >${cmtOECEventtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtOECEventtempfile}
  unset cmtOECEventtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtOECEventtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtOECEventtempfile}
unset cmtOECEventtempfile
return $cmtsetupstatus

