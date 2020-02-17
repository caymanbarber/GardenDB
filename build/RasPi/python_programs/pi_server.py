from http.server import ThreadingHTTPServer, BaseHTTPRequestHandler
from io import BytesIO
import socketserver

import data_processor


class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        body = self.rfile.read(content_length)
        newbody=body.decode("utf-8")
        data_processor.writeJSONCSV(newbody,"CSV_Data_test.csv")
        self.send_response(200)
        self.end_headers()
        response = BytesIO()
        response.write(b'Post recieved\n')
        self.wfile.write(response.getvalue())

class myServer(ThreadingHTTPServer):
    def startMyServer(self):
        try:
            self.serve_forever()
        except KeyboardInterrupt:
            data_processor.logError("KeyboardInterrupt", "Shut server down manually")
            print("\nServer manually shut down\n")
            pass
        except Exception as e:
            print("Server shut down due to error\n")
            data_processor.logError(e, "Shut server down unexpectedly")
        finally:
            self.server_close()
