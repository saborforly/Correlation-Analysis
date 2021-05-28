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
    parser.add_argument("--inputdir",default="",help="input file name")
    parser.add_argument("--inputlist", default=["/junofs/users/liuyan2016/OEC/oec-prototype/OEC.root"],action='append', help="the file")

    parser.add_argument("--outputdir", default="/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/share/", help="output file name")
    
    return parser

DATA_LOG_MAP = {"Test":0, "Debug":2, "Info":3, "Warn":4, "Error":5, "Fatal":6}
import RootIOSvc
import BufferMemMgr
parser=get_parser()
args = parser.parse_args()

def create_data(outputFile, evtmax, time):
    
    task_top = Sniper.TopTask("OECTask")
    task_top.setEvtMax(evtmax)
    task_top.setLogLevel(0)
    #subTask buffer calibEvent

    #import TagSelectSvc
    #riSvc = task_top.createSvc("RootInputSvc/InputSvc")
    #riSvc.property("InputFile").set(args.inputlist)
     
    roSvc = task_top.createSvc("RootOutputSvc/OutputSvc")
    outputdata = {"/Event/OEC": outputFile}
    roSvc.property("OutputStreams").set(outputdata)

    bufMgr = task_top.createSvc("BufferMemMgr")
    bufMgr.property("TimeWindow").set([-100, 100]);

    

    import DataGen
    bufalg=task_top.createAlg("DataGenAlg")
    bufalg.property("time").set(time);
    #For test get Result
    #task.property("algs").append("ExampleGetResult")
    task_top.show()
    task_top.run()

if __name__ == "__main__":
    outputdir = args.outputdir
    evtmax = args.evtmax
    file_object = open('/junofs/users/liuyan2016/OEC/oec-prototype/Tag/DataGen/fileId.txt', 'w')
    evtmax = 5000000

    for i in range(1):
        time = i*evtmax 
        outputFile = outputdir+str(i)+"_OEC.root"
        file_object.writelines(outputFile+"\n")
        create_data(outputFile,evtmax, time)
    file_object.close( )


