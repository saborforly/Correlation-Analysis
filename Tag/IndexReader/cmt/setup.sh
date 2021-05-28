# echo "setup IndexReader v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtIndexReadertempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtIndexReadertempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=IndexReader -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  -no_cleanup $* >${cmtIndexReadertempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=IndexReader -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  -no_cleanup $* >${cmtIndexReadertempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtIndexReadertempfile}
  unset cmtIndexReadertempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtIndexReadertempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtIndexReadertempfile}
unset cmtIndexReadertempfile
return $cmtsetupstatus

