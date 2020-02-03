from http.server import ThreadingHTTPServer, BaseHTTPRequestHandler
from io import BytesIO
##from tbd_change_csv_file import tbd_classs

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        body = self.rfile.read(content_length)
        print(body)
        #send body to parser in tbd class
        self.send_response(200)
        self.end_headers()
        response = BytesIO()
        response.write(b'Post request recieved ')
        self.wfile.write(response.getvalue())
        #print(self.rfile.read(content_length))



httpd = ThreadingHTTPServer(("localhost", 8000), SimpleHTTPRequestHandler)
httpd.serve_forever()
