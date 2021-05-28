# echo "cleanup OECEvent v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtOECEventtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtOECEventtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=OECEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana  $* >${cmtOECEventtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=OECEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana  $* >${cmtOECEventtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtOECEventtempfile}
  unset cmtOECEventtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtOECEventtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtOECEventtempfile}
unset cmtOECEventtempfile
exit $cmtcleanupstatus

