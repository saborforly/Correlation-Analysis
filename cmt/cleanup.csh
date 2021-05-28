# echo "cleanup cor-ana v0 in /hpcfs/juno/junogpu/liuyan2016"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtcor_anatempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtcor_anatempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=cor-ana -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016  $* >${cmtcor_anatempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=cor-ana -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016  $* >${cmtcor_anatempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtcor_anatempfile}
  unset cmtcor_anatempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtcor_anatempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtcor_anatempfile}
unset cmtcor_anatempfile
exit $cmtcleanupstatus

