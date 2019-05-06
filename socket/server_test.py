import socket
import sys

# HOST = "0.0.0.0"
HOST = "192.168.0.28"
PORT = 7800

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    s.bind((HOST, PORT))
except:
    print("Error: Socket bind failed.")
    sys.exit()

print("Info: Socket bind complete.")

s.listen(10)
conn, addr = s.accept()
print("Info: Connected to " + addr[0] + ':' + str(addr[1]))

# Above passed
while 1:
    data = conn.recv(10)
    if data:
        print "received data:", data

# conn.close()
# s.close()
