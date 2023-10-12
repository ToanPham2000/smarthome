Mô hình nhà thông minh gồm chức năng:
-	Cửa chính đóng mở cửa bằng bộ đọc thẻ từ RFID. Khi chạm đúng thẻ RFID thì cửa sẽ tự động mở nếu sai thì hiển thị lên màn hình LCD thông báo thử lại.
-	Có thể điều khiển đóng mở từ xa qua internet cửa bằng cách nhập mật khẩu trên webserver.
-	Cảm biến khí gas cảnh báo và tự động bật tắt quạt thông gió.
-	Đo nhiệt độ, độ ẩm hiển thị lên màn hình LCD.
-	Cảm biến nước mưa tự động thu quần áo.
-	Cảm biến ánh sáng tự động bật tắt đèn.
-	Bật tắt các thiết bị qua internet và giọng nói.
![z4568368815493_32c9d24dc2caa742c23726ae1a305c25](https://github.com/ToanPham2000/home/assets/142808050/bfd34531-00ae-4bde-8909-0c70c94dd408)
Sử dụng html,css tạo giao diện cho truy cập webserver ESP8266 để thực hiện điều khiển các cơ cấu chấp hành tương ứng:
Xây dựng trợ lý ảo bằng python:
- Thư viện:
  - speech_recognition: Nhận dạng giọng nói thành văn bản
  - pyttsx3: Chuyển văn bản thành giọng nói
  - paho-mqtt: gửi nhận tin nhắn qua MQTT
