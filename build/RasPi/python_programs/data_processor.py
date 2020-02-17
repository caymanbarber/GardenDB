import sys
import json
import os.path

def writeJSONCSV(inputStr,CSVFile):

    jsonData = json.loads(inputStr)
    CSVOutput = JSONtoCSV(jsonData)

    if os.path.isfile(CSVFile):
        try:
            with open(CSVFile, "a") as f:
                f.write(CSVOutput)
                f.close()
        except Exception as e:
            print("\nError printing to \n")
            exit() #add exception here to keep things running maybe add error log
    else:
        try:
            print("CSV file does not exist\nCreating new file")
            with open(CSVFile, "w+") as fn:
                fn.write("time,device,sensor,value\n")
                fn.write(CSVOutput + "\n")
                fn.close()
        except:
            print("Tried to create file. CSV file does not exist\n")
            exit()

def JSONtoCSV(jsonData):
    csvOut = jsonData["time"] + ", " + jsonData["device"] + ", " +  jsonData["sensor"] + ", " + str(jsonData["value"])
    return csvOut
