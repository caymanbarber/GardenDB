import sys
import json
import os.path
import datetime

def writeJSONCSV(inputStr,CSVFile):

    jsonData = json.loads(inputStr)
    CSVOutput = JSONtoCSV(jsonData)

    if os.path.isfile(CSVFile): #if file exists append data to csv file
        try:
            with open(CSVFile, "a") as f:
                f.write(CSVOutput + "\n")
                f.close()
        except Exception as e:
            print("Error logging to file\n error: "+e+"\n")
            logError(e, "Appending data to CSV file")
    else:                       #if file does not exist create then add data to csv file
        try:
            print("CSV file does not exist\nCreating new file\n")
            with open(CSVFile, "w+") as f:
                f.write("time,device,sensor,value\n")
                f.write(CSVOutput + "\n")
                f.close()
        except Exception as e:
            print("Tried to create file. CSV file does not exist\nerror: "+e+"\n")
            logError(e, "Creating CSV file and adding data. (CLOSING)")
            exit()

def JSONtoCSV(jsonData):    #turn string JSON to text to print to csv file
    csvOut = jsonData["time"] + ", " + jsonData["device"] + ", " +  jsonData["sensor"] + ", " + str(jsonData["value"])
    return csvOut

def logError(e, context):   #given error and context save errors to file
    logFile = "ErrorLog.txt"
    time = datetime.datetime.now()

    if not context:
        context = "no context"

    if os.path.isfile(logFile):
        with open(logFile, "a") as f:
            f.write(str(time)+" error: " + e + " context: " + context +"\n")
            f.close()
    else:
        with open(logFile, "w+") as f:
            f.write("Error for python sever below\n")
            f.write(str(time)+" error: " + e + " context: " + context + "\n")
            f.close()
