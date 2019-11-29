# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .loading.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 18:18:56 by lubenard          #+#    #+#              #
#    Updated: 2019/11/27 15:50:16 by lubenard         ###   ########.fr        #
#    Updated: 2019/11/19 16:17:55 by frossiny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/usr/env python3

import sys
from time import sleep
from time import time as now
import os
from pathlib import Path

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
    result = Path("/tmp/makefile_42sh").read_text().strip()
    if result:
        i = int(result)
    else:
        i = 0
else:
    i = 0

l = len(items) - 1
start_time = now()
# Initial call to print 0% progress
if i < l:
    printProgressBar(start_time, i + 1, l, length = 50, printEnd="")
    makefile_42sh = open("/tmp/makefile_42sh", 'w')
    makefile_42sh.write(str(i + 1))
    makefile_42sh.close()
else:
    os.system("rm /tmp/frossiny/makefile_42sh")
