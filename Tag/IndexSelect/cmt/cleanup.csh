# echo "cleanup IndexSelect v0 in /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v1r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtIndexSelecttempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtIndexSelecttempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=IndexSelect -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  $* >${cmtIndexSelecttempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=IndexSelect -version=v0 -path=/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag  $* >${cmtIndexSelecttempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtIndexSelecttempfile}
  unset cmtIndexSelecttempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtIndexSelecttempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtIndexSelecttempfile}
unset cmtIndexSelecttempfile
exit $cmtcleanupstatus

