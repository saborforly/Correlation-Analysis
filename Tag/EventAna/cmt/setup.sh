# echo "setup EventAna v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtEventAnatempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtEventAnatempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=EventAna -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  -no_cleanup $* >${cmtEventAnatempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=EventAna -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  -no_cleanup $* >${cmtEventAnatempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtEventAnatempfile}
  unset cmtEventAnatempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtEventAnatempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtEventAnatempfile}
unset cmtEventAnatempfile
return $cmtsetupstatus

