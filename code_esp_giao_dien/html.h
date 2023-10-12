const char MainPage[] PROGMEM = R"=====(
<!DOCTYPE html> 
<html>
 <head> 
  <meta charset="UTF-8">
  <title>Đọc nhiệt độ độ ẩm</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
  <link rel="icon" href="data:,">
  <script src="https://code.highcharts.com/highcharts.js"></script> 
     <style> 
     html {
            font-family: Arial;
            display: inline-block;
            text-align: center;
        }
        p {
            font-size: 1.2rem;
        }

        body {
            margin: 0;
        }

        .tieude {
            overflow: hidden;
            background-color: #4B1D3F;
            color: white;
            font-size: 1.7rem;
        }

        .content {
            padding: 8px;          
        }

        .card {
        background-color: white;
        box-shadow: 2px 2px 12px 1px rgba(140, 140, 140,2);
        border-radius: 10px;
        padding: 10px;
        margin-bottom: 10px;
        display: inline-block;
        text-align: center;
        width: 250px;
        margin: 8px;
    }
    .password {
    margin-bottom: 10px;
    margin: 10px;
   }
    .mk {
    background-color: white;
    box-shadow: 2px 2px 12px 1px rgba(140, 140, 140,2);
    border-radius: 10px;
    padding: 10px;
    margin-bottom: 10px;
    display: none;
    text-align: center;
    width: 250px;
    margin: 8px;
    }
    .mk.show{
    display: inline-block;
    }
    .led {
        text-align: center;
        margin-bottom: 10px;
        font-size: 2rem;
        color: #4B1D3F;
    }
    .led-icon {
        padding-top: 10px;
        color: #4B1D3F;
        font-size: 2rem;
    }
        a {text-decoration: none;color:#FFFFFF;}
        .bt_off {height:50px; width:100px; margin:10px 0;background-color:#FF6600;border-radius:5px;font-size: 1.5rem}
        .bt_on {height:50px; width:100px; margin:10px 0;background-color:#00FF00;border-radius:5px;font-size: 1.5rem}
        .sensor-value {font-size: 3rem; color: #4B1D3F;}
        .sensor {text-align: center; margin-bottom: 10px; }
        .btn-toggle {
      position: relative;
      display: inline-block;
      width: 60px;
      height: 34px;
      margin-right: 10px;
    }
  
    .btn-toggle input[type="checkbox"] {
      opacity: 0;
      width: 0;
      height: 0;
    }
  
    /* Đặt màu nền và border-radius cho nút */
    .btn-toggle .slider {
      position: absolute;
      cursor: pointer;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background-color: #ccc;
      border-radius: 34px;
      -webkit-transition: .4s;
      transition: .4s;
    }
  
    /* Đặt màu nền cho nút khi bật */
    .btn-toggle input[type="checkbox"]:checked + .slider {
      background-color: #28A745;
    }
  
    /* Đặt màu nền cho nút khi tắt */
    .btn-toggle input[type="checkbox"] + .slider {
      background-color: #FF4136;
    }
  
    /* Đặt border-radius và box-shadow cho nút khi bật */
    .btn-toggle input[type="checkbox"]:checked + .slider:before {
      -webkit-transform: translateX(26px);
      -ms-transform: translateX(26px);
      transform: translateX(26px);
      border-radius: 50%;
      box-shadow: 0px 0px 5px 1px rgba(255, 65, 54, 0.5);
    }
  
    /* Đặt border-radius cho nút khi tắt */
    .btn-toggle .slider:before {
      position: absolute;
      content: "";
      height: 26px;
      width: 26px;
      left: 4px;
      bottom: 4px;
      background-color: white;
      -webkit-transition: .4s;
      transition: .4s;
      border-radius: 50%;
    }
     </style>
     <meta charset="UTF-8">
 </head>
 <body> 
    <div class="tieude">
      <h1>Nhà của Toàn Shino</h1>
    </div>
    <div class="password">
      <label for="password">Mật khẩu:</label>
      <input type="password" id="password">
      <button onclick="checkPassword()">Xác nhận</button>
    </div>
    <div class="cards">
      <div class="mk">
        <div class="led">
          <i class="fas fa-lightbulb led-icon"></i>Cửa 
          <div> </div>
          <!-- Thay đổi button thành button kiểu gạt -->
          <label class="btn-toggle">
            <input type="checkbox" onclick="toggle('cua')">
            <span class="slider"></span>
          </label>
        </div>
      </div>
      <div class="card">
        <div class="led">
          <i class="fas fa-lightbulb led-icon"></i>Voice 
          <div> </div>
          <!-- Thay đổi button thành button kiểu gạt -->
          <label class="btn-toggle">
            <input type="checkbox" onclick="toggle('voice')">
            <span class="slider"></span>
          </label>
        </div>
      </div>
    </div>
  <div class="cards">
    <h1>Phòng khách</h1>
  </div>
  <div class="content">
    <div class="card">
      <div class="sensor">
        <div class="sensor-value"><i class="fas fa-thermometer-half"></i>
        Nhiệt độ <div><span id="idtemperature1">0</span>&deg;C</div>
        </div>
      </div>
    </div>
    <div class="card">
      <div class="sensor">
        <div class="sensor-value"><i class="fas fa-tint "></i>
        Độ ẩm <div><span id="idhumidity1">0</span>%</div>
        </div>
      </div>
    </div>
  </div>
  <div class="card">
    <div class="led">
      <i class="fas fa-lightbulb led-icon"></i>Bóng đèn 
      <div> </div>
      <!-- Thay đổi button thành button kiểu gạt -->
      <label class="btn-toggle">
        <input type="checkbox" onclick="toggle('denkhach')">
        <span class="slider"></span>
      </label>
    </div>
  </div>
  <div class="card">
    <div class="led">
      <i class="fas fa-lightbulb led-icon"></i>Quạt 
      <div> </div>
      <!-- Thay đổi button thành button kiểu gạt -->
      <label class="btn-toggle">
        <input type="checkbox" onclick="toggle('quatkhach')">
        <span class="slider"></span>
      </label>
    </div>
  </div>
    <div class="cards">
      <h1>phòng ngủ</h1>
    </div>
    <div class="content">
      <div class="card">
        <div class="sensor">
          <div class="sensor-value"><i class="fas fa-thermometer-half "></i>
          Nhiệt độ <div><span id="idtemperature2">0</span>&deg;C</div>
          </div>
        </div>
      </div>
      <div class="card">
        <div class="sensor">
          <div class="sensor-value"><i class="fas fa-tint "></i>
          Độ ẩm <div><span id="idhumidity2">0</span>%</div>
          </div>
        </div>
      </div>
    </div>
      <div class="card">
        <div class="led">
          <i class="fas fa-lightbulb led-icon"></i>Bóng đèn 
          <div> </div>
          <!-- Thay đổi button thành button kiểu gạt -->
          <label class="btn-toggle">
            <input type="checkbox" onclick="toggle('denngu')">
            <span class="slider"></span>
          </label>
        </div>
      </div>
      <div class="card">
        <div class="led">
          <i class="fas fa-lightbulb led-icon"></i>Quạt 
          <div> </div>
          <!-- Thay đổi button thành button kiểu gạt -->
          <label class="btn-toggle">
            <input type="checkbox" onclick="toggle('quatngu')">
            <span class="slider"></span>
          </label>
        </div>
      </div>
    </div>
    <div class="cards">
      <h1>phòng tắm và sân phơi </h1>
    </div>
    <div class="card">
      <div class="led">
        <i class="fas fa-lightbulb led-icon"></i>Phòng tắm<i class="fas fa-lightbulb led-icon"></i>
        <div> </div>
        <!-- Thay đổi button thành button kiểu gạt -->
        <label class="btn-toggle">
          <input type="checkbox" onclick="toggle('phongtam')">
          <span class="slider"></span>
        </label>
      </div>
    </div>
    <div class="card">
      <div class="led">
        <i class="fas fa-lightbulb led-icon"></i>Sân phơi 
        <div> </div>
        <!-- Thay đổi button thành button kiểu gạt -->
        <label class="btn-toggle">
          <input type="checkbox" onclick="toggle('sanphoi')">
          <span class="slider"></span>
        </label>
      </div>
    </div>
  </div>
  <script>
    function checkPassword() {
    var password = document.getElementById("password").value;
    if (password == "123") { 
        document.querySelector(".mk").classList.add("show");
    } else {
        document.querySelector(".mk").classList.remove("show");
    }
    }
    var ledState = {
    'cua': false,
    'voice': false,
    'denkhach': false,
    'quatkhach': false,
    'denngu': false,
    'quatngu': false,
    'phongtam': false,
    'sanphoi': false
    };
    function toggle(id) {
      ledState[id] = !ledState[id];
      var xhttp = new XMLHttpRequest();
      if (ledState[id]) {
        xhttp.open("GET","/on" + id,true);
      } else {
        xhttp.open("GET","/off" + id,true);
      }
      xhttp.send();
    }
    setInterval(function(){
      getnhietdo1();
      getdoam1();
      getnhietdo2();
      getdoam2();
    },2000);
    function getnhietdo1() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200) {
          document.getElementById("idtemperature1").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET","docnhietdo1",true);
      xhttp.send();
    }
    function getdoam1() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200) {
          document.getElementById("idhumidity1").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET","docdoam1",true);
      xhttp.send();
    }
    function getnhietdo2() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200) {
          document.getElementById("idtemperature2").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET","docnhietdo2",true);
      xhttp.send();
    }
    function getdoam2() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if(this.readyState == 4 && this.status == 200) {
          document.getElementById("idhumidity2").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET","docdoam2",true);
      xhttp.send();
    }
    </script>
    <script>
      var toggleBtn = document.querySelector('.btn-toggle');
      toggleBtn.addEventListener('click', function() {
      toggleBtn.classList.toggle('active');
      });
  </script>
 </body>
</html>
)=====";