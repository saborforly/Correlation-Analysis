#!/usr/bin/env python
# -*- coding:utf-8 -*-
# author: liuyan

# using the new Mgr.

import Sniper
def get_parser():
    import argparse

    parser=argparse.ArgumentParser(description='run Tag')
    parser.add_argument("--loglevel",default="Info",choices=["Test","Debug","Info","Warn","Error","Fatal"],help="set the log level")
    parser.add_argument("--evtmax",type=int,default=400000,help="events to be processed")

    parser.add_argument("--id",type=float,default=0,help="events to be processed")

    parser.add_argument("--pathfile",default="/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/pathfile.txt",help="input file name")

    parser.add_argument("--outputfile", default="/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/0_OEC.root", help="output file name")
    
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
    bufMgr.property("TimeWindow").set([0, 0]);

    

    import DataGen
    bufalg=task_top.createAlg("DataGenRateAlg")
    #bufalg=task_top.createAlg("DataGenIBDAlg")
    bufalg.property("time").set(time);
    bufalg.property("pathfile").set(args.pathfile);
    RateMap={"K40":0.518, "Th232":0.81, "U238":3.472}
    bufalg.property("RateMap").set(RateMap);
    #For test get Result
    #task.property("algs").append("ExampleGetResult")
    task_top.show()
    task_top.run()

if __name__ == "__main__":
    outputfile = args.outputfile
    evtmax = args.evtmax
    #file_object = open('/junofs/users/liuyan2016/OEC/oec-prototype/Tag/DataGen/fileId.txt', 'w')

    for i in range(1,2):
        #time = i*evtmax
        time = 0 
        outputfile = args.outputfile+str(args.id)+"_OEC.root"
        #outputfile = args.outputfile+"0_OEC.root"
        #file_object.writelines(outputFile+"\n")
        create_data(outputfile,evtmax, time)
    #file_object.close( )


