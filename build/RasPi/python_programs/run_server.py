import pi_server
from http.server import ThreadingHTTPServer, BaseHTTPRequestHandler


httpd = pi_server.myServer(("localhost", 8000), pi_server.SimpleHTTPRequestHandler)
httpd.startMyServer()
