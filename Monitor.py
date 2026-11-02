#!/usr/bin/env python3
import json
import subprocess
import sys

colect = subprocess.run("./colect", capture_output=True, text=True)

def ExecuteColect():
    if colect.returncode != 0:
        print("Erro To Load Memory Available And Load")
        sys.exit("Nothing To Do")
    else:
        print(colect)

def ConvertText(text):
    text = colect.stdout
    a = json.loads(text)
    print(a["load1"])

ExecuteColect()
