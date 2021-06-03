# echo "cleanup IBDEvent v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtIBDEventtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtIBDEventtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=IBDEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  $* >${cmtIBDEventtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=IBDEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  $* >${cmtIBDEventtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtIBDEventtempfile}
  unset cmtIBDEventtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtIBDEventtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtIBDEventtempfile}
unset cmtIBDEventtempfile
return $cmtcleanupstatus

