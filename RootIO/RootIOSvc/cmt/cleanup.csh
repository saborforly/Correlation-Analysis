# echo "cleanup RootIOSvc v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana/RootIO"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtRootIOSvctempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtRootIOSvctempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=RootIOSvc -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/RootIO  $* >${cmtRootIOSvctempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=RootIOSvc -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/RootIO  $* >${cmtRootIOSvctempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtRootIOSvctempfile}
  unset cmtRootIOSvctempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtRootIOSvctempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtRootIOSvctempfile}
unset cmtRootIOSvctempfile
exit $cmtcleanupstatus

