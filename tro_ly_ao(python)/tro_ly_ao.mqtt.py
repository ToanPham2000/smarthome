import os
import speech_recognition
import pyttsx3
# import tkinter
# from tkinter import *
from datetime import datetime
import paho.mqtt.client as mqtt
import requests
import json
import subprocess

# Cài đặt địa chỉ IP và cổng của broker MQTT
broker_address = "192.168.250.100"
broker_port = 1883

# Cài đặt tên client và các đường dẫn topic
client_id = "PC"
switch_topic = "switch"
giong_noi = "voice"

now = datetime.now()
ngay = now.strftime("%d")
thang = now.strftime("%m")
nam = now.strftime("%Y")
gio = now.strftime("%H")
phut = now.strftime("%M")
# Lấy ngày hiện tại
ngay_hien_tai = datetime.now().date()

# Ngày họp
ngay_hop = datetime(2023, 8, 15).date() 
def ngay_bao_ve():
    if ngay_hien_tai == ngay_hop:
        result = "Hôm nay bạn có buổi bảo vệ đồ án tốt nghiệp. Thứ tự bảo vệ của bạn là 15."
    else:
        result = "Hôm nay bạn không có việc gì cả."
    return result

API_KEY = "10bd7b2054827915e711b57e5a00ec4c"  # Thay YOUR_API_KEY bằng API key của bạn từ OpenWeatherMap

def get_current_weather(city):
    base_url = "https://api.openweathermap.org/data/2.5/weather"
    params = {
        "q": city,
        "appid": API_KEY,
        "units": "metric"  # Đơn vị Celsius
    }

    response = requests.get(base_url, params=params)
    data = json.loads(response.text) #chuyển chuỗi văn bản sang json

    if data["cod"] == "404":
        return "Không tìm thấy thông tin thời tiết cho thành phố này."
    
    weather_description = data["weather"][0]["description"]
    temperature = data["main"]["temp"]
    humidity = data["main"]["humidity"]
    rain = False

    if "rain" in data:
        rain = True

    weather_mapping = {
        "clear sky": "Trời quang",
        "few clouds": "Ít mây",
        "scattered clouds": "Mây rải rác",
        "broken clouds": "Mây rải rác",
        "overcast clouds": "Mây u ám",
        "shower rain": "Mưa rào",
        "rain": "Mưa",
        "thunderstorm": "Dông",
        "snow": "Tuyết",
        "mist": "Sương mù"
    }

    weather_description_vn = weather_mapping.get(weather_description, weather_description)
    result = f"Thời tiết hôm nay tại {city}: {weather_description_vn}, nhiệt độ {temperature} độ C, độ ẩm {humidity} phần trăm. "

    if rain:
        result += "Hôm nay sẽ có mưa. Bạn nên mang áo mưa khi ra ngoài."
    else:
        result += "Hôm nay không mưa."

    return result

music_player_process = None
is_music_playing = False

def start_music_player():
    global music_player_process, is_music_playing
    player_path = "C:\\Program Files (x86)\\Windows Media Player\\wmplayer.exe"  # Thay thế bằng đường dẫn thực tế đến file .exe của trình phát nhạc
    music_path = "D:\\nhac\\NhacChill.mp3"
    # Khởi chạy trình phát nhạc
    music_player_process = subprocess.Popen([player_path, music_path])
    is_music_playing = True

def stop_music_player():
    global music_player_process, is_music_playing
    if music_player_process:
        # Tắt trình phát nhạc
        music_player_process.terminate()
        music_player_process = None
        is_music_playing = False
#khai bao cac bien, cai dat giong noi tieng viet
language = 'vi'   
Robot_listen = speech_recognition.Recognizer()         
Robot_talk = pyttsx3.init()                      
Robot_think = ""                          

# Kết nối đến broker MQTT
client = mqtt.Client(client_id)
client.connect(broker_address, broker_port)
client.subscribe(switch_topic)
# client.subscribe(giong_noi)

def send_control_message(message):
    # Gửi thông điệp điều khiển đến broker MQTT
    client.publish(switch_topic, message)

flag = False
a = False
# chaomung = False
voices = Robot_talk.getProperty("voices")
Robot_talk.setProperty("voice", voices[1].id)
def on_message(client, userdata, message):
    global a
    msg = str(message.payload.decode("utf-8"))
    # print(msg)
    if msg == "batgiongnoi":
        a = True
    elif msg == "tatgiongnoi":
        a = False
client.on_message = on_message

while True:
    client.loop()  
    if a:
        if not flag:
            with speech_recognition.Microphone() as mic:
                Robot_listen.adjust_for_ambient_noise(mic) 
                print("Robot: Tôi đang nghe")
                audio = Robot_listen.listen(mic)
            
            print("Robot: ...")
            
            try:
                you = Robot_listen.recognize_google(audio, language=language)
            except:
                you = ""
            
            print("You: " + you)
            
            if "bật robot" in you:
                flag = True
                Robot_think = "Xin chào! Tôi là trợ lý của Phạm Đức Toàn. Tôi có thể giúp gì được cho bạn?"
                print("Robot: " + Robot_think)
                Robot_talk.say(Robot_think)
                Robot_talk.runAndWait()
        else:
            with speech_recognition.Microphone() as mic:
                Robot_listen.adjust_for_ambient_noise(mic) 
                print("Robot: Tôi đang nghe")
                audio = Robot_listen.listen(mic)
            
            print("Robot: ...")
            
            try:
                you = Robot_listen.recognize_google(audio, language=language)
            except:
                you = ""
            
            print("You: " + you)
            
            if you == "":
                Robot_think = "Tôi không nghe thấy bạn. Bạn cần tôi giúp gì?"
            else:
                if "Xin chào" in you:
                    Robot_think = "Chào bạn! Bạn muốn tôi giúp gì?"
                elif "mở cửa" in you:
                    Robot_think = "Vui lòng nhập mật khẩu để mở cửa."
                    print("Robot: " + Robot_think)
                    Robot_talk.say(Robot_think)
                    Robot_talk.runAndWait()
                    
                    with speech_recognition.Microphone() as mic:
                        Robot_listen.adjust_for_ambient_noise(mic) 
                        audio = Robot_listen.listen(mic)
                    
                    try:
                        password = Robot_listen.recognize_google(audio, language=language)
                    except:
                        password = ""
                    print("You: " + password)
                    # if check_password(password):
                    if "123" in password:
                        send_control_message("mocua")
                        Robot_think = "Đã mở cửa"
                    else:
                        Robot_think = "Mật khẩu sai. Không thể mở cửa."
                elif "đóng cửa" in you:
                    send_control_message("dongcua")
                    Robot_think = "Đã đóng cửa"
                elif "bật đèn phòng khách" in you:
                    send_control_message("batdenkhach")
                    Robot_think = "Đèn phòng khách đã bật"
                elif "Tắt đèn phòng khách" in you:
                    send_control_message("tatdenkhach")
                    Robot_think = "Đèn phòng khách đã tắt"
                elif "bật quạt phòng khách" in you:
                    send_control_message("batquatkhach")
                    Robot_think = "Quạt phòng khách đã bật"
                elif "tắt quạt phòng khách" in you:
                    send_control_message("tatquatkhach")
                    Robot_think = "Quạt phòng khách đã tắt"
                elif "bật đèn phòng ngủ" in you:
                    send_control_message("batdenngu")
                    Robot_think = "Đèn phòng ngủ đã bật"
                elif "Tắt đèn phòng ngủ" in you:
                    send_control_message("tatdenngu")
                    Robot_think = "Đèn phòng ngủ đã tắt"
                elif "bật đèn phòng tắm" in you:
                    send_control_message("batphongtam")
                    Robot_think = "Đèn phòng tắm đã bật"
                elif "Tắt đèn phòng tắm" in you:
                    send_control_message("tatphongtam")
                    Robot_think = "Đèn phòng tắm đã tắt"
                elif "thu quần áo" in you:
                    send_control_message("batthuquanao")
                    Robot_think = "Đã thu quần áo"
                elif "phơi quần áo" in you:
                    send_control_message("tatthuquanao")
                    Robot_think = "Đã phơi quần áo"
                elif "tắt hết đi" in you:
                    send_control_message("tatdenkhach")
                    send_control_message("tatquatkhach")
                    send_control_message("tatdenngu")
                    send_control_message("tatquatngu")
                    send_control_message("tatphongtam")
                    # send_control_message("thuquanao")
                    Robot_think = "Đã tắt hết mọi thứ"
                elif "Hôm nay ngày bao nhiêu" in you:
                    Robot_think = f"Hôm nay là ngày {ngay}, tháng {thang}, năm {nam}"
                elif "mấy giờ" in you:
                    Robot_think = f"Bây giờ là {gio} giờ, {phut} phút"
                elif "Hôm nay có việc gì không" in you:
                    ngay_bao_ve = ngay_bao_ve()
                    Robot_think = ngay_bao_ve
                    # if ngay_hien_tai == ngay_hop:
                    #     Robot_think = "Hôm nay bạn buổi bảo vệ đồ án tốt nghiệp. "
                    # else:
                    #     Robot_think = "Hôm nay bạn không có việc gì cả"
                elif "mở nhạc" in you:
                    # music_dir = 'D:\\nhac'          # thư mục để nhạc
                    # songs = os.listdir(music_dir)
                    # os.startfile(os.path.join(music_dir,songs[0]))
                    start_music_player()
                    Robot_think = "Tôi đã mở nhạc cho bạn"
                elif "Tắt nhạc" in you:
                    stop_music_player()
                    Robot_think = "Tôi đã tắt nhạc cho bạn"
                elif "thời tiết hôm nay" in you:
                    city = "Hanoi" 
                    weather_info = get_current_weather(city)
                    Robot_think = weather_info
                elif "Thời tiết nơi khác" in you:
                    Robot_think = "Bạn muốn biết thời tiết ở nơi nào?"
                    print("Robot: " + Robot_think)
                    Robot_talk.say(Robot_think)
                    Robot_talk.runAndWait()

                    with speech_recognition.Microphone() as mic:
                        Robot_listen.adjust_for_ambient_noise(mic)
                        audio = Robot_listen.listen(mic)

                    try:
                        tp = Robot_listen.recognize_google(audio, language=language)
                    except speech_recognition.UnknownValueError:
                        tp = ""
                    print("You: " + tp)
                    city = tp  # Đặt tên thành phố bạn muốn tra cứu thời tiết
                    weather_info = get_current_weather(city)
                    Robot_think = weather_info
                elif "tạm biệt" in you:
                    Robot_think = "Tạm biệt"
                    flag = False
                elif "dừng" in you:
                    Robot_think = "Tạm biệt"
                    flag = False
                else:
                    Robot_think = "Xin lỗi. Tôi không hiểu lệnh của bạn!"
            
            print("Robot: " + Robot_think)
            Robot_talk.say(Robot_think)
            Robot_talk.runAndWait()