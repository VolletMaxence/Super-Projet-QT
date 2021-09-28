navigator.tcpPermission.requestPermission({remoteAddress:"127.0.0.1", remotePort:4321}).then(
    () => {
      // Permission was granted
      // Create a new TCP client socket and connect to remote host
      var mySocket = new TCPSocket("127.0.0.1", 4321);
      // Send data to server
      mySocket.writeable.write("Hello World").then(
          () => {
              // Data sent sucessfully, wait for response
              console.log("Data has been sent to server");
              mySocket.readable.getReader().read().then(
                  ({ value, done }) => {
                      if (!done) {
                          // Response received, log it:
                          console.log("Data received from server:" + value);
                      }
                      // Close the TCP connection
                      mySocket.close();
                  }
              );
          },
          e => console.error("Sending error: ", e)
      );
    }
  );