#!/usr/bin/env python
def get_parser():
    import argparse

    parser=argparse.ArgumentParser(description='run Tag')
    parser.add_argument("--loglevel",default="Info",choices=["Test","Debug","Info","Warn","Error","Fatal"],help="set the log level")
    parser.add_argument("--sel",type=int,default=1,help="events to be processed")
    parser.add_argument("--ana",type=int,default=3,help="events to be processed")

    return parser

DATA_LOG_MAP = {"Test":0, "Debug":2, "Info":3, "Warn":4, "Error":5, "Fatal":6}
parser=get_parser()
args = parser.parse_args()

print("sel",args.sel)
print("ana",args.ana)


def TagIO():
    import Sniper
    task = Sniper.Task("TagIO")
    import TagIO
    #riSvc = task.createSvc("IOInputSvc/InputSvc")
    IObufMgr = task.createSvc("TagIOMemMgr")
    IObufMgr.property("TimeWindow").set([-1.1, 1000000]);
    IObufMgr.property("pathFile").set("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy-OEC/fileId_0.5M.txt");
    IObufMgr.property("tagFile").set("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/background/mergy-OEC/tag_0.5M.txt");
    #import BufferMemMgr
    #riSvc = task.createSvc("TagIOSvc/InputSvc")
    #bufMgr = task.createSvc("BufferMemMgr")
    #bufMgr.property("TimeWindow").set([-100, 100]);

    task.show()
    return task

def TagAna():
    # configuration is just the same as a single thread job
    import Sniper
    global ath
    ath += 1
    task = Sniper.Task(str(ath) +"-TagAna")

    import TagAna
    bufMgr = task.createSvc("TagWinMemMgr")
    iSvc = task.createSvc("WinInputSvc/InputSvc")
    oSvc = task.createSvc("WinOutputSvc/OutputSvc")

    bufalg=task.createAlg("TagAnaEvent")

    task.show()
    return task

def TagWriter():
    import Sniper
    task = Sniper.Task("TagWriter")
    import TagWriter
    wa = task.createAlg("GBufPopAlg")
    #wa = task.createAlg("GTagInfoPopAlg")
    wa.property("DataFile").set("data.file")

    return task

if __name__ == "__main__":

    import Sniper
    Sniper.setLogLevel(3)
    #0 all, 3 Info
    #Sniper.setShowTime()
    #Sniper.setLogFile("log.txt", False)
    import time
    import SniperMuster
    muster = SniperMuster.Muster()

    global sth
    sth = 0

    global ath
    ath = 0    


    # the EvtMax in Sniper.Task is deactivated by Muster
    muster.setEvtMax(50000)

    # we will execute the TagAna maximumly in 4 threads
    muster.configAna(TagAna, args.ana)


    # I/O and global buffer
    gs = SniperMuster.GlobalStream("GEvtStream")
    gs.configIO(TagIO)
    gs.configOutput(TagWriter)
    gs.configBuffer(40, 20)

    # TODO: show the configurations
    #muster.show()

    # spawn the threads and begin to run 
    muster.run()
