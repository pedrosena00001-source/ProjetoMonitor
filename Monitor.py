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
    logging.basicConfig(filename="MonitorLog.log", filemode="w", format="%(asctime)s - %(levelname)s - %(message)s", level=logging.DEBUG)
    if colect.returncode == 0:
        logging.debug("Operation Works Well")
    else:
        logging.debug("Operation Didnt Works Well")
        VerifyColect()


def Main():
    VerifyColect()
    ConvertText(text=colect)
    Log()
    if MemAvailable >= 5:
        print("Caution Our MemAvailable Is Nearly To End")

Main()
