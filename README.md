## Simple Web Client Program
This project is a simple web client that uses TCP and SSL protocols. Users can select a protocol (TCP/SSL) to perform HTTP or HTTPS communication.

### ✅ Features
- Support for switching between TCP (HTTP) and SSL (HTTPS)
- UI controls for entering host, sending messages, connecting/disconnecting
- Communication with servers via TCP and SSL sockets
- Display connection status dynamically on the UI
- Real-time reception and display of server responses
- Able to send messages like `GET / HTTP/1.1` with `Host: www.example.com`

### 🖥️ UI Components
- Host input field: Enter server address
- Connect button: Connect via HTTP or HTTPS
- Send button: Send custom messages to server
- Message display area: Shows server responses
- Connection status label: Indicates TCP/SSL connection status
- Protocol selector: Choose between HTTP (TCP) and HTTPS (SSL)

### 🚀 How to Use
1. When the program starts, TCP (HTTP) is selected by default
2. Enter the server address (e.g., `www.naver.com`)
3. Select SSL if HTTPS is needed
4. Click the Connect button
5. Type a message and click Send
6. Server response will be displayed in the message area
7. Use Disconnect button to close the connection

### 💡 Code Summary
- `tcpSocket_` and `sslSocket_` manage TCP and SSL sockets respectively
- `protocol` value determines communication type (80 for TCP, 443 for SSL)
- UI labels update with "Connected", "Disconnected", etc.
- Messages are sent to the server, and responses are displayed in real-time

<br><br>
![webclient](https://github.com/user-attachments/assets/ab5caef5-734b-456d-943e-306fafbe0697)

