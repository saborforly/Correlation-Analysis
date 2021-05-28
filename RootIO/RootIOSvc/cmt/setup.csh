# echo "setup RootIOSvc v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana/RootIO"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtRootIOSvctempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtRootIOSvctempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=RootIOSvc -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/RootIO  -no_cleanup $* >${cmtRootIOSvctempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=RootIOSvc -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/RootIO  -no_cleanup $* >${cmtRootIOSvctempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtRootIOSvctempfile}
  unset cmtRootIOSvctempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtRootIOSvctempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtRootIOSvctempfile}
unset cmtRootIOSvctempfile
exit $cmtsetupstatus

