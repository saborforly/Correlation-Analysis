#!/bin/bash
pushd /hpcfs/juno/junogpu/liuyan2016/cor-ana/
source setup.sh
python  /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/mergy.py --output /hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/Th232-12080.root --input /junofs/production/data-production/Pre-Releases/J20v1r0-Pre2/background/LS/Th232/1000812080/detsim/detsim-11*.root
