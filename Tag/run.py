#!/usr/bin/env python
def get_parser():
    import argparse

    parser=argparse.ArgumentParser(description='run Tag')
    parser.add_argument("--loglevel",default="Info",choices=["Test","Debug","Info","Warn","Error","Fatal"],help="set the log level")
    parser.add_argument("--sel",type=int,default=3,help="events to be processed")
    parser.add_argument("--ana",type=int,default=3,help="events to be processed")

    return parser

DATA_LOG_MAP = {"Test":0, "Debug":2, "Info":3, "Warn":4, "Error":5, "Fatal":6}
parser=get_parser()
args = parser.parse_args()

print("sel",args.sel)
print("ana",args.ana)

def IndexReader():
    import Sniper
    task = Sniper.Task("IndexReader")
    import IndexReader
    mMgr = task.createSvc("IndexReaderMemMgr")
    mMgr.property("pathFile").set("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/fileId.txt");
    mMgr.property("tagFile").set("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/tag.txt");
    #mMgr.property("pathFile").set("/junofs/users/liuyan2016/OEC/oec-prototype/Tag/DataGen/testFileId.txt");
    #mMgr.property("tagFile").set("/junofs/users/liuyan2016/OEC/oec-prototype/Tag/DataGen/testTag.txt");
    task.show()
    return task


def IndexSelect():
    import Sniper
    global sth
    sth += 1
    task = Sniper.Task(str(sth) +"-EventSelect")
    import IndexSelect
    riSvc = task.createSvc("SelectInputSvc/InputSvc")

    import BufferMemMgr
    bufMgr = task.createSvc("SelectMemMgr")

    bufalg=task.createAlg("FirstFilterAlg")

    task.show()
    #fa = task.createAlg("FillGBufAlg")
    #fa.property("GenMax").set(-1)

    return task

def IndexEventIO():
    import Sniper
    task = Sniper.Task("IndexEventIO")
    import IndexEventIO
    #riSvc = task.createSvc("IOInputSvc/InputSvc")
    IObufMgr = task.createSvc("IndexEventIOMemMgr")
    IObufMgr.property("TimeWindow").set([-1.1, 1.1]);
    #import BufferMemMgr
    #riSvc = task.createSvc("TagIOSvc/InputSvc")
    #bufMgr = task.createSvc("BufferMemMgr")
    #bufMgr.property("TimeWindow").set([-100, 100]);

    task.show()
    return task

def EventAna():
    # configuration is just the same as a single thread job
    import Sniper
    global ath
    ath += 1
    task = Sniper.Task(str(ath) +"-EventAna")

    import EventAna
    bufMgr = task.createSvc("EventWinMemMgr")
    iSvc = task.createSvc("WinInputSvc/InputSvc")
    oSvc = task.createSvc("WinOutputSvc/OutputSvc")

    bufalg=task.createAlg("EventAnaAlg")

    global first_time
    task.show()
    return task

def EventWriter():
    import Sniper
    task = Sniper.Task("TagWriter")
    import EventWriter
    wa = task.createAlg("GBufPopAlg")
    #wa = task.createAlg("GTagInfoPopAlg")
    wa.property("DataFile").set("data.file")

    return task

if __name__ == "__main__":

    import Sniper
    Sniper.setLogLevel(0)
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

    global first_time
    first_time = True

    # the EvtMax in Sniper.Task is deactivated by Muster
    muster.setEvtMax(1000)

    # we will execute the TagAna maximumly in 4 threads
    muster.configSelect(IndexSelect, args.sel)
    muster.configAna(EventAna, args.ana)


    # I/O and global buffer
    gs = SniperMuster.GlobalStream("GEvtStream")
    gs.configInput(IndexReader)
    gs.configIO(IndexEventIO)
    gs.configOutput(EventWriter)
    gs.configBuffer(40, 20)

    # TODO: show the configurations
    #muster.show()

    # spawn the threads and begin to run 
    muster.run()
