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
        response.write(b'Post recieved')
        self.wfile.write(response.getvalue())

httpd = ThreadingHTTPServer(("localhost", 8000), SimpleHTTPRequestHandler)
try:
    httpd.serve_forever()
except:
    print("Server shut down\n")
