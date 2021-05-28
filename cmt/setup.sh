# echo "setup cor-ana v0 in /hpcfs/juno/junogpu/liuyan2016"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtcor_anatempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtcor_anatempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=cor-ana -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016  -no_cleanup $* >${cmtcor_anatempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=cor-ana -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016  -no_cleanup $* >${cmtcor_anatempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtcor_anatempfile}
  unset cmtcor_anatempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtcor_anatempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtcor_anatempfile}
unset cmtcor_anatempfile
return $cmtsetupstatus

