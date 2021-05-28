#!/usr/bin/env python
# -*- coding:utf-8 -*-

import sys

if __name__ == '__main__':
  import argparse
  parser = argparse.ArgumentParser(description='merge data model files.')
  parser.add_argument("--output", help="output filename")
  parser.add_argument("--input", nargs='+', help="output filename")

  args = parser.parse_args()

  # check the existance
  import os.path
  if os.path.exists(args.output):
    print "%s already exists."%args.output
    print "Please remove it before merge"
    sys.exit(-1)

  import Sniper
  task = Sniper.Task("task")
  task.setLogLevel(3)

  import RootIOTools
  import glob

  mfalg = task.createAlg("MergeRootFilesAlg/mfalg")
  fileList = []
  for fn in sys.argv[1:-1]:
    fileList += glob.glob(fn)
  fileList = list(set(fileList))
  mfalg.property("InputFiles").set(args.input)
  mfalg.property("OutputFile").set(args.output)

  task.setEvtMax(-1)
  task.show()
  task.run()
