import socket

# Tạo socket để nhận dữ liệu từ Qt (trên cổng 12347)
udp_receiver = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_receiver.bind(("127.0.0.1", 12347))
print("Python đang lắng nghe trên cổng 12347 để nhận dữ liệu từ Qt...")

# Tạo socket riêng để gửi tín hiệu đến Qt (trên cổng 12346)
udp_sender = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
qt_address = ("127.0.0.1", 12346)

# Gửi tín hiệu ban đầu đến Qt
udp_sender.sendto("parking signal".encode(), qt_address)

while True:
    data, addr = udp_receiver.recvfrom(1024)
    message2 = data.decode()
    print(f"Nhận từ {addr}: {message2}")

    if message2 == "Yes":
        print("🚗 Bật chế độ đỗ xe tự động!")
    elif message2 == "No":
        print("⛔ Không kích hoạt chế độ đỗ xe tự động!")
