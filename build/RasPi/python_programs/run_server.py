import pi_server
from http.server import ThreadingHTTPServer, BaseHTTPRequestHandler


httpd = pi_server.myServer(("172.20.10.2", 8000), pi_server.SimpleHTTPRequestHandler)
httpd.startMyServer()
