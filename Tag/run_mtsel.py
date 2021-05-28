#!/usr/bin/env python
def get_parser():
    import argparse

    parser=argparse.ArgumentParser(description='run Tag')
    parser.add_argument("--loglevel",default="Info",choices=["Test","Debug","Info","Warn","Error","Fatal"],help="set the log level")
    parser.add_argument("--sel",type=int,default=1,help="events to be processed")
    parser.add_argument("--ana",type=int,default=1,help="events to be processed")

    return parser

DATA_LOG_MAP = {"Test":0, "Debug":2, "Info":3, "Warn":4, "Error":5, "Fatal":6}
parser=get_parser()
args = parser.parse_args()

print("sel",args.sel)
print("ana",args.ana)

def TagReader():
    import Sniper
    task = Sniper.Task("TagReader")
    import TagReader
    mMgr = task.createSvc("TagReaderMemMgr")
    mMgr.property("pathFile").set("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/fileId.txt");
    mMgr.property("tagFile").set("/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/tag.txt");
    #mMgr.property("pathFile").set("/junofs/users/liuyan2016/OEC/oec-prototype/Tag/DataGen/testFileId.txt");
    #mMgr.property("tagFile").set("/junofs/users/liuyan2016/OEC/oec-prototype/Tag/DataGen/testTag.txt");
    task.show()
    return task


def TagSelect():
    import Sniper
    global sth
    sth += 1
    task = Sniper.Task(str(sth) +"-TagSelect")
    import TagSelect
    riSvc = task.createSvc("SelectInputSvc/InputSvc")

    import BufferMemMgr
    bufMgr = task.createSvc("SelectMemMgr")

    bufalg=task.createAlg("FirstFilterAlg")

    task.show()
    #fa = task.createAlg("FillGBufAlg")
    #fa.property("GenMax").set(-1)

    return task

def TagWriter():
    import Sniper
    task = Sniper.Task("TagWriter")
    import TagWriter
    print("OK")
    #wa = task.createAlg("GBufPopAlg")
    wa = task.createAlg("GTagInfoPopAlg")
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
    muster.configSelect(TagSelect, args.sel)

    # I/O and global buffer
    gs = SniperMuster.GlobalStream("GEvtStream")
    gs.configInput(TagReader)
    gs.configOutput(TagWriter)
    gs.configBuffer(40, 20)

    # TODO: show the configurations
    #muster.show()

    # spawn the threads and begin to run 
    muster.run()
