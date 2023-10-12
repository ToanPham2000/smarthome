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
        .sensor-value {font-size: 3rem; color: #4B1D3F;}
        .sensor {text-align: center; margin-bottom: 10px; }
     </style>
     <meta charset="UTF-8">
 </head>
 <body> 
    <div class="tieude">
      <h1>Nhà của Phạm Đức Toàn</h1>
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
    <div class="content">
      <div class="card-grid">
            <p class="card-title">Nhiệt độ</p>
            <div id="chart-temperature1" class="chart-container"></div>
        </div>
      </div>
      <div class="card-grid">
        <p class="card-title"></p>
        <div id="chart-temperature2" class="chart-container"></div>
    </div>
  </div>
    <div class="content">
      <div class="card-grid">
              <p class="card-title">Độ ẩm</p>
              <div id="chart-humidity1" class="chart-container"></div>
        </div>
      <div class="card-grid">
              <p class="card-title"></p>
              <div id="chart-humidity2" class="chart-container"></div>
        </div>
    </div>
   <script>
      setInterval(function(){
        getnhietdo1();
        getdoam1();
        getnhietdo2();
        getdoam2();
      },1000);
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
      var chartT = new Highcharts.Chart({
        chart: { renderTo: 'chart-temperature1' },
        title: { text: 'Nhiệt độ phòng khách' },
        series: [{ showInLegend: false, data: [] }],
        plotOptions: { line: { animation: false, dataLabels: { enabled: true } }, series: { color: '#059e8a' } },
        xAxis: { type: 'datetime', dateTimeLabelFormats: { second: '%H:%M:%S' } },
        yAxis: { title: { text: 'Temperature (Celsius)' } },
        credits: { enabled: false }
        });

        var chartH = new Highcharts.Chart({
        chart: { renderTo: 'chart-humidity1' },
        title: { text: 'Độ ẩm phòng khách' },
        series: [{ showInLegend: false, data: [] }],
        plotOptions: { line: { animation: false, dataLabels: { enabled: true } } },
        xAxis: { type: 'datetime', dateTimeLabelFormats: { second: '%H:%M:%S' } },
        yAxis: { title: { text: 'Humidity' } },
        credits: { enabled: false }
        });

      var chartT2 = new Highcharts.Chart({
        chart: { renderTo: 'chart-temperature2' },
        title: { text: 'Nhiệt độ phòng ngủ' },
        series: [{ showInLegend: false, data: [] }],
        plotOptions: { line: { animation: false, dataLabels: { enabled: true } }, series: { color: '#059e8a' } },
        xAxis: { type: 'datetime', dateTimeLabelFormats: { second: '%H:%M:%S' } },
        yAxis: { title: { text: 'Temperature (Celsius)' } },
        credits: { enabled: false }
      });
      var chartH2 = new Highcharts.Chart({
        chart: { renderTo: 'chart-humidity2' },
        title: { text: 'Độ ẩm phòng ngủ' },
        series: [{ showInLegend: false, data: [] }],
        plotOptions: { line: { animation: false, dataLabels: { enabled: true } }, series: { color: '#059e8a' } },
        xAxis: { type: 'datetime', dateTimeLabelFormats: { second: '%H:%M:%S' } },
        yAxis: { title: { text: 'Humidity' } },
        credits: { enabled: false }
      });

        function updateChart(chart, url) {
        setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
        var date = new Date();
        date.setHours(date.getHours() + 7)
        var x = date.getTime(),
        y = parseFloat(this.responseText);
        if (chart.series[0].data.length > 20) {
        chart.series[0].addPoint([x, y], true, true, true);
        } else {
        chart.series[0].addPoint([x, y], true, false, true);
        }
        sessionStorage.setItem('chartData', JSON.stringify(chart.series[0].data));
        }
        };
        xhttp.open("GET", url, true);
        xhttp.send();
        }, 5000);
        }

        updateChart(chartT, "/docnhietdo1");
        updateChart(chartH, "/docdoam1");
        updateChart(chartT2, "/docnhietdo2");
        updateChart(chartH2, "/docdoam2");
        var storedData = JSON.parse(sessionStorage.getItem('chartData'));
        if (storedData) {
        for (var i = 0; i < storedData.length; i++) {
        chartT.series[0].addPoint(storedData[i], false, false, false);
        }
        }
  </script>
 </body>
</html>
)=====";