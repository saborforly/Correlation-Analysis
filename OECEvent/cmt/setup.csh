# echo "setup OECEvent v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtOECEventtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtOECEventtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=OECEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana  -no_cleanup $* >${cmtOECEventtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=OECEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana  -no_cleanup $* >${cmtOECEventtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtOECEventtempfile}
  unset cmtOECEventtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtOECEventtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtOECEventtempfile}
unset cmtOECEventtempfile
exit $cmtsetupstatus

