#pragma once

const char DASHBOARD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Kicker Counter</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <link rel="stylesheet" href="/style.css">
  <style>
    h1 {
      font-size: 1.5rem;
      text-align: center;
      color: #ffffff;
      margin-bottom: 1.5rem;
    }
    h2 {
      font-size: 1rem;
      text-align: center;
      color: #ffffff;
      margin-bottom: 1.25rem;
    }
    label {
      display: block;
      margin-top: 1rem;
      font-weight: bold;
      color: #cccccc;
    }
    p {
      text-align: center;
      color: #cccccc;
      margin-top: .25rem;
      font-size: .75rem;
    }
    .disconnect {
        display: flex;
        flex-direction: row;
        justify-content: center;
        background: #eb4040ff;
    }
  </style>
</head>
<body class="scrollbar-hide flex flex-col m-0 p-2 min-h-screen justify-center text-white font-sans">
    <div class="container mx-auto flex flex-col justify-center">
        <h1>Kicker Counter</h1>
        <div class="card mt-2 p-2 md:w-96 w-full bg-gray-900 border-none rounded-lg">
            <h2>Stand</h2>
            <label for="ssid">Stand</label>
            <span id="counter">0</span>

            <label for="ssid">Spielzeit</label>
            <span id="playtime">--:--</span>

            <button class="flex w-full p-2 mt-2 items-center bg-blue-500 hover:bg-blue-600 justify-center text-white border-none rounded cursor-pointer" onclick="resetScore()">
                <div class="h-6 w-6 mr-2 stroke-2">
                    <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1" stroke-linecap="round" stroke-linejoin="round"><path d="M9 11l-4 4l4 4m-4 -4h11a4 4 0 0 0 0 -8h-1" /></svg>
                </div>
                <span>Zurücksetzen</span>
            </button>
            <button class="flex w-full p-2 mt-2 items-center bg-red-500 hover:bg-red-600 justify-center text-white border-none rounded cursor-pointer" onclick="reset()">
                <div class="h-6 w-6 mr-2 stroke-2">
                    <svg xmlns="http://www.w3.org/2000/svg"viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1" stroke-linecap="round" stroke-linejoin="round"><path d="M20 16l-4 4" /><path d="M7 12l5 5l-1.5 1.5a3.536 3.536 0 1 1 -5 -5l1.5 -1.5z" /><path d="M17 12l-5 -5l1.5 -1.5a3.536 3.536 0 1 1 5 5l-1.5 1.5z" /><path d="M3 21l2.5 -2.5" /><path d="M18.5 5.5l2.5 -2.5" /><path d="M10 11l-2 2" /><path d="M13 14l-2 2" /><path d="M16 16l4 4" /></svg>
                </div>
                <span>Verbindung trennen</span>
            </button>
        </div>
        <p>ESP32 C6 - {{IP}} ({{MAC}})</p>
    </div>
  
    <script>
        let gameStartEpoch = 0;

        async function updateScore() {
            const res = await fetch("/status");
            const data = await res.json();
            document.getElementById("counter").textContent = data.scoreA + ":" + data.scoreB;
        }
        function formatTime(seconds) {
            const min = Math.floor(seconds / 60);
            const sec = seconds % 60;
            if (min < 0 || sec < 0) {
                return "--:--";
            } else {
                return String(min).padStart(2, '0') + ':' + String(sec).padStart(2, '0');
            }
        }
        function updateSpielzeit() {
            if (!gameStartEpoch) return;
            const now = Math.floor(Date.now() / 1000);  // aktuelle Zeit in Sekunden
            const diff = now - gameStartEpoch;
            document.getElementById("playtime").textContent = formatTime(diff);
        }
        async function startGameClock() {
            const res = await fetch("/gamestart");
            const unix = await res.text();
            gameStartEpoch = parseInt(unix, 0);
            setInterval(updateSpielzeit, 1000);
        }
        async function resetScore() {
            await fetch("/gamereset");
            updateScore();
            startGameClock();
        }
        async function reset() {
            await fetch("/reset");
        }
        setInterval(updateScore, 2000);
        updateScore();
        startGameClock();
    </script>
</body>
</html>
)rawliteral";