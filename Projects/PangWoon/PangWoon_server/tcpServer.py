import socket, threading
import tcpServerThread

class TCPServer(threading.Thread):
    def __init__(self, commandQueue, HOST, PORT):
        threading.Thread.__init__(self)
        self.commandQueue = commandQueue
        self.HOST = HOST
        self.PORT = PORT
        self.client_Number=0
        self.serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) # For binding error, added this code.
        self.serverSocket.bind((self.HOST, self.PORT))
        self.serverSocket.listen(1)
        self.tcpServerThreads = ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20',
                                 '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31', '32', '33', '34', '35',
                                 '36', '37', '38', '39', '40', '41', '42', '43', '44', '45', '46', '47', '48', '49', '50']

    def run(self):
        try:
            while True:
                #print('tcp server :: server wait...')
                connection, clientAddress = self.serverSocket.accept()

                print("Client :: ", clientAddress[1], " is connected.")
                subThread = tcpServerThread.TCPServerThread(self.commandQueue, connection, clientAddress)
                subThread.start()
                self.tcpServerThreads[clientAddress[1]%50]=subThread

        except:
            print("Server :: Thread error")

    def sendAll(self, port_number, message):
        try:
            print("Server :: sending data to", port_number, " -> ", message) 
            self.tcpServerThreads[port_number%50].send(message)
        except:
            pass
