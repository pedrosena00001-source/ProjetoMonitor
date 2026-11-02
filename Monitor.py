#!/usr/bin/env python3
import json
import subprocess
import sys
import logging

colect = subprocess.run("./colect", capture_output=True, text=True)

def VerifyColect():
    if colect.returncode != 0:
        sys.exit("Error To Load Memory Or Load")

def ConvertText(text):
    text = colect.stdout
    a = json.loads(text)
    global MemAvailable
    MemTotal = (a["mem_total_kb"] /1000000)
    MemAvailable = (a["mem_available_kb"] /1000000)
    Load = (a["load1"])
    print(f"MemTotal: {MemTotal:.2f} gB")
    print(f"MemAvailable: {MemAvailable:.2f} gB")
    print(f"Load: {Load}")

def Log():
    logger = logging.getLogger()
    logger.setLevel(logging.DEBUG)
    fh = logging.FileHandler("Monitor.log")
    fh.setLevel(logging.DEBUG)
    logger.addHandler(fh)
    if colect.returncode == 0:
        logger.debug('The Program Works Well')
    else:
        logger.debug('The Program Dindt Works Well')
        VerifyColect()

def Main():
    VerifyColect()
    ConvertText(text=colect)
    Log()
    if MemAvailable >= 5:
        print("Caution Our MemAvailable Is Nearly To End")

Main()
