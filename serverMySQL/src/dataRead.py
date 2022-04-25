#!/usr/bin/env python3

import serial
import time
import requests
import json
import datetime

api_url = "http://localhost:3000"

while(1):
    try:
        device = serial.Serial("/dev/ttyACM0", 9600)
        time.sleep(2.0)

        resp = device.readline()
        _json = resp.decode(encoding='UTF-8',errors='strict')

        data = json.loads(_json)
        crrt_time = datetime.datetime.now()

        x = {
            "robot_id": 1,
            "temperature": data["temperature"],
            "weight": data["weight"],
            "timedate": str(crrt_time),
            "powerState": "10"
        }

        jsonMsg = json.dumps(x)
        response = requests.post(api_url, data=jsonMsg)
        print(jsonMsg)
        
    except KeyboardInterrupt:
        break
    except:
        pass