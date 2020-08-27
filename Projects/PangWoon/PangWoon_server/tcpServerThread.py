import socket, threading


class TCPServerThread(threading.Thread):
    def __init__(self, commandQueue, connection, clientAddress):
        threading.Thread.__init__(self)

        self.commandQueue = commandQueue
        self.connection = connection
        self.clientAddress = clientAddress

    def run(self):
        try:
            while True:
                data = self.connection.recv(1024).decode()

                # when break connection
                if not data:
                    print("Client :: ", self.clientAddress[1], " is disconnected.")
                    break

                print("Client :: ", self.clientAddress[1], " sending data.", " -> ", data)
                self.commandQueue.put([self.clientAddress[1],data])
        except:
            exit(0)

    def send(self, message):
        print("Server :: sending data to ", self.clientAddress[1], " Success.")
        try:
            self.connection.sendall(message.encode())
        except:
            pass


