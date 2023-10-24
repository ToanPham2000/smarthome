Mô hình nhà thông minh gồm chức năng:
-	Cửa chính đóng mở cửa bằng bộ đọc thẻ từ RFID. Khi chạm đúng thẻ RFID thì cửa sẽ tự động mở nếu sai thì hiển thị lên màn hình LCD thông báo thử lại.
-	Có thể điều khiển đóng mở từ xa qua internet cửa bằng cách nhập mật khẩu trên webserver.
-	Cảm biến khí gas cảnh báo và tự động bật tắt quạt thông gió.
-	Đo nhiệt độ, độ ẩm hiển thị lên màn hình LCD.
-	Cảm biến nước mưa tự động thu quần áo.
-	Cảm biến ánh sáng tự động bật tắt đèn.
-	Bật tắt các thiết bị qua internet và giọng nói.

![z4568368815493_32c9d24dc2caa742c23726ae1a305c25](https://github.com/ToanPham2000/home/assets/142808050/bfd34531-00ae-4bde-8909-0c70c94dd408)
![image](https://github.com/ToanPham2000/smarthome/assets/142808050/bab8a495-cddb-420e-a28a-8c5a5dcc1484)

Giao thức truyèn thông:
- UART: giao tiếp giữa Arduino và ESP
- SPI: giao tiếp giữa Arduino và RC-522
- MQTT: giao tiếp giữa các ESP và trợ lý ảo thông qua broker MQTT
Sử dụng thư viện ESP8266WebServer và ngôn ngữ đánh dấu html,css tạo giao diện cho truy cập webserver ESP8266 để thực hiện điều khiển các cơ cấu chấp hành tương ứng

![image](https://github.com/ToanPham2000/smarthome/assets/142808050/3533aba3-0be6-4638-a3e6-76b13a181287)

Xây dựng trợ lý ảo bằng python:
- Thư viện sử dụng:
  - speech_recognition: Nhận dạng giọng nói thành văn bản
  - pyttsx3: Chuyển văn bản thành giọng nói
  - paho-mqtt: gửi nhận tin nhắn từ broker MQTT (mosquitto)
  - requests: gửi các yêu cầu HTTP và xử lý các phản hồi (lấy thông tin thời tiết từ openweathermap)
  - subprocess: thực thi các lệnh hệ thống từ Python
- Sử dụng broker mosquitto kết nối giữa trợ lý ảo và esp giúp trợ lý ảo có thể điều khiển các thiết bị bằng cách publish tới chủ đề mình cài và esp sẽ subcribe chủ đề đó. 

Chức năng trợ lý ảo:
- Điều khiển các thiết bị trong nhà
- Tra thông tin thời tiết
- Thông báo lịch làm việc, mở nhạc

Video thực hiện

https://www.youtube.com/watch?v=PdVACyaYFmE

https://www.youtube.com/watch?v=WEzeviP4wOg
