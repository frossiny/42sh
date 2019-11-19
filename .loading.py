# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .loading.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lubenard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 18:18:56 by lubenard          #+#    #+#              #
#    Updated: 2019/11/16 17:18:24 by lubenard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/usr/env python3

import sys
from time import sleep
from time import time as now
import os
import subprocess

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def printProgressBar (start_time, iteration, total, prefix = '', suffix = '', decimals = 1, length = 100, fill = '█', printEnd = "\r"):
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + ' ' * (length - filledLength)
    ETA = 0
    if iteration > 0:
        ETA = 100 / (100 * iteration / total) * (now() - start_time)
    print('\r%s %s%%  |{}%s{}| {}%s{}%10s'.format(bcolors.OKGREEN, bcolors.ENDC, bcolors.OKBLUE,bcolors.ENDC) % ( prefix, percent,bar,sys.argv[1], suffix), end=printEnd)
    if iteration == total:
        print()

items = []
root = "./srcs/"
path = os.path.join(root, ".")

for path, subdirs, files in os.walk(root):
    for name in files:
        items.append(os.path.join(path, name))

if os.path.isfile("/tmp/makefile_42sh"):
    result = subprocess.run(['cat', '/tmp/makefile_42sh'], stdout=subprocess.PIPE)
    i = int(result.stdout.decode('utf-8'))
    makefile_42sh = open("/tmp/makefile_42sh", 'w')
else:
    i = -1
    #print("File does not exist")
    makefile_42sh = open("/tmp/makefile_42sh", 'w')

l = len(items) - 5
start_time = now()
# Initial call to print 0% progress
if i < l:
    printProgressBar(start_time, i + 1, l, length = 50, printEnd="")
    makefile_42sh.write(str(i + 1))
    makefile_42sh.close()
else:
    os.system("rm /tmp/makefile_42sh")
