import socket
import time
import random

udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = ("127.0.0.1", 12345)  # IP và cổng của Qt

try:
    while True:
        value1 = random.randint(0, 280)  # Giá trị ngẫu nhiên từ 50 đến 150
        value2 = random.randint(1, 3)  # Giá trị ngẫu nhiên từ 1 đến 5
        value3 = random.randint(0, 100)  # Giá trị ngẫu nhiên từ 0 đến 100

        message = f"{value1}_{value2}_{value3}\n"
        udp_socket.sendto(message.encode(), server_address)
        print(f"Đã gửi: {message.strip()}")
        time.sleep(1)  # Gửi mỗi giây
except KeyboardInterrupt:
    print("\nDừng gửi dữ liệu.")
    udp_socket.close()