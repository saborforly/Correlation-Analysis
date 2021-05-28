#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: liuyan

# using the new Mgr.

import Sniper
def get_parser():
    import argparse

    parser=argparse.ArgumentParser(description='run Tag')
    parser.add_argument("--loglevel",default="Info",choices=["Test","Debug","Info","Warn","Error","Fatal"],help="set the log level")
    parser.add_argument("--evtmax",type=int,default=1000,help="events to be processed")
    parser.add_argument("--rate",  type=float,default=0.1,help="events to be processed")

    parser.add_argument("--inputdir", default="/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/share/", help="output file name")
    
    return parser

DATA_LOG_MAP = {"Test":0, "Debug":2, "Info":3, "Warn":4, "Error":5, "Fatal":6}
import RootIOSvc
import BufferMemMgr
parser=get_parser()
args = parser.parse_args()

def read_data(inputFile, evtmax, fileID):
    
    task_top = Sniper.TopTask("OECTask")
    task_top.setEvtMax(-1)
    task_top.setLogLevel(0)
    #subTask buffer calibEvent

    #import TagSelectSvc
    riSvc = task_top.createSvc("RootInputSvc/InputSvc")
    riSvc.property("InputFile").set(inputFile)
     
    #roSvc = task_top.createSvc("RootOutputSvc/OutputSvc")
    #outputdata = {"/Event/OEC": outputFile}
    #roSvc.property("OutputStreams").set(outputdata)

    bufMgr = task_top.createSvc("BufferMemMgr")
    bufMgr.property("TimeWindow").set([0, 0]);

    

    import DataGen
    bufalg=task_top.createAlg("DataReadAlg")
    bufalg.property("fileID").set(fileID);
    bufalg.property("lowEnergy").set(args.rate);
    #For test get Result
    #task.property("algs").append("ExampleGetResult")
    task_top.show()
    task_top.run()

if __name__ == "__main__":
    inputFile = args.inputdir
    fo = open("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/fileId.txt", "w+")
    for i in range(1):
        #inputFile = inputdir+"OEC-800k.root"
        fo.write(str(i)+'\t'+inputFile+'\n')
        #inputFile =["/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/4_OEC.root","/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/5_OEC.root"]
        read_data(inputFile,args.evtmax, i)
    
    fo.close()

