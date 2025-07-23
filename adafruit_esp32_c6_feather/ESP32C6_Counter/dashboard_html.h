#pragma once

const char DASHBOARD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Kicker COunter</title>
  <style>
    * {
        -webkit-user-select: none
        -khtml-user-select: none
        -moz-user-select: none
        -ms-user-select: none
        user-select: none
    }
    *,
    *::before,
    *::after {
        box-sizing: border-box;
    }
    .scrollbar-hide {
        -ms-overflow-style: none;
        scrollbar-width: none;
        overflow-y: scroll;
        &::-webkit-scrollbar {
            display: none;
            width: 0;
            height: 0;
        }
    }
    body {
      font-family: Arial, sans-serif;
      background: #121212;
      color: #f0f0f0;
      margin: 0;
      padding: 2rem;
      display: flex;
      flex-direction: column;
      justify-content: center;
      min-height: 100vh;
    }
    .card {
      background: #1e1e1e;
      padding: 2rem;
      border-radius: 1rem;
      box-shadow: 0 6px 16px rgba(0, 0, 0, 0.6);
      max-width: 400px;
      width: 100%;
      margin-top: 2rem;
    }
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
    button {
        height: 40px;
        width: 100%;
        padding: 0.75rem;
        margin-top: 1.5rem;
        background: #2196f3;
        color: white;
        border: none;
        border-radius: 0.5rem;
        font-size: 1rem;
        cursor: pointer;
        transition: background 0.3s;

        span {
            margin-left: 8px;
        }
    }
    button:hover {
      background: #1976d2;
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
<body class="scrollbar-hide">
  <h1>Kicker Counter</h1>
  <div class="card">
    <h2>Stand</h2>
    <label for="ssid">Stand</label>
    <div id="counter">0</div>

    <label for="ssid">Spielzeit</label>
    <div id="playtime">--:--</div>

    <button onclick="resetScore()">
        <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1" stroke-linecap="round" stroke-linejoin="round"><path d="M9 11l-4 4l4 4m-4 -4h11a4 4 0 0 0 0 -8h-1" /></svg>
        <span>Zurücksetzen</span>
    </button>
    <button class="disconnect" onclick="reset()">
        <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1" stroke-linecap="round" stroke-linejoin="round"><path d="M20 16l-4 4" /><path d="M7 12l5 5l-1.5 1.5a3.536 3.536 0 1 1 -5 -5l1.5 -1.5z" /><path d="M17 12l-5 -5l1.5 -1.5a3.536 3.536 0 1 1 5 5l-1.5 1.5z" /><path d="M3 21l2.5 -2.5" /><path d="M18.5 5.5l2.5 -2.5" /><path d="M10 11l-2 2" /><path d="M13 14l-2 2" /><path d="M16 16l4 4" /></svg>
        <span>Verbindung trennen</span>
    </button>
  </div>
  <p>ESP32 C6 - {{IP}} ({{MAC}})</p>
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
        return String(min).padStart(2, '0') + ':' + String(sec).padStart(2, '0');
    }
    function updateSpielzeit() {
        if (!gameStartEpoch) return;
        const now = Math.floor(Date.now() / 1000);  // aktuelle Zeit in Sekunden
        const diff = now - gameStartEpoch;
        document.getElementById("playtime").textContent = formatTime(diff);
    }
    async function startGameClock() {
        const res = await fetch("/unixtime");
        const unix = await res.text();
        gameStartEpoch = parseInt(unix, 10);
        updateSpielzeit();
        setInterval(updateSpielzeit, 1000);
    }
    async function resetScore() {
      await fetch("/goalreset");
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