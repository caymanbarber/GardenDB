import sys
import json

class HandleInput:

    @staticmethod
    def writeJSONCSV(inputStr,CSVFile):

        jsonData = json.loads(inputStr)

        CSVOutput = JSONtoCSV(jsonData)

        with open(CSVFile, 'w') as f:
            try:
                f.write(CSVOutput)
                f.close()
            except:
                try:
                    print("CSV file does not exist\nCreating new file")
                    with open(CSVFile, "w+") as fn:
                        fn.write("time,device,sensor,value")
                        fn.write(CSVOutput)
                        fn.close()
                except:
                    print("CSV file does not exist\n")
                    exit()

    @staticmethod
    def JSONtoCSV(jsonData):
        csvOut = jsonData["time"] + ", " + jsonData["device"] + ", " +  jsonData["sensor"] + ", " + jsonData["value"]
        return csvOut
