# echo "setup IBDEvent v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtIBDEventtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtIBDEventtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=IBDEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  -no_cleanup $* >${cmtIBDEventtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=IBDEvent -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  -no_cleanup $* >${cmtIBDEventtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtIBDEventtempfile}
  unset cmtIBDEventtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtIBDEventtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtIBDEventtempfile}
unset cmtIBDEventtempfile
exit $cmtsetupstatus
