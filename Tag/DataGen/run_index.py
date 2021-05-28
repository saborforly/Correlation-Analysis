#!/usr/bin/env python
def get_parser():
    import argparse

    parser=argparse.ArgumentParser(description='run Tag')
    parser.add_argument("--loglevel",default="Info",choices=["Test","Debug","Info","Warn","Error","Fatal"],help="set the log level")
    parser.add_argument("--tagFile",default="/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/tag.txt",help="set the log level")    
    parser.add_argument("--pathFile",default="/hpcfs/juno/junogpu/liuyan2016/cor-ana/Tag/DataGen/fileId.txt",help="set the log level")
    return parser

DATA_LOG_MAP = {"Test":0, "Debug":2, "Info":3, "Warn":4, "Error":5, "Fatal":6}
parser=get_parser()
args = parser.parse_args()


def IndexIO(tagFile, pathFile):
    import Sniper
    task = Sniper.Task("IndexIO")
    import DataGen
    task.setLogLevel(0)
    IObufMgr = task.createSvc("TagIndexMemMgr")
    IObufMgr.property("TimeWindow").set([0, 0]);
    IObufMgr.property("pathFile").set(pathFile);
    IObufMgr.property("tagFile").set(tagFile);

    task.show()
    task.run()
if __name__ == "__main__":
    for i in range(5):
        tagFile = args.tagFile
        pathFile = args.pathFile
        IndexIO(tagFile,pathFile)
