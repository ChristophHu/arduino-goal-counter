#pragma once

const char AP_HTML_HEAD[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ESP32 WLAN Konfiguration</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
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
    .select-wrapper {
        position: relative;
        display: flex;
        align-items: center;
    }
    .select-wrapper select {
        appearance: none;
        -webkit-appearance: none;
        -moz-appearance: none;
        width: 100%;
        padding: 0.75rem 2.5rem 0.75rem 0.75rem; /* rechts Platz für Icon */
        font-size: 1rem;
        border-radius: 0.5rem;
        background: #2a2a2a;
        color: #f0f0f0;
        border: 1px solid #444;
        box-sizing: border-box;
    }
    .select-wrapper .select-icon {
        position: absolute;
        right: 1rem;
        pointer-events: none;
        width: 1rem;
        height: 1rem;
        fill: #aaa;
    }
    select, input {
      width: 100%;
      padding: 0.5rem;
      margin-top: 0.25rem;
      border: 1px solid #444;
      border-radius: 0.5rem;
      font-size: 1rem;
      background: #2a2a2a;
      color: #f0f0f0;
    }
    button {
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
    .loading {
      font-style: italic;
      color: #aaaaaa;
      margin-top: 0.75rem;
    }
  </style>
</head>
<body class="scrollbar-hide">
    <h1>Kicker Counter</h1>
    <div class="card">
        <h2>WLAN konfigurieren</h2>
        <form action="/save" method="get" autocomplete="off">
        <label for="ssid">SSID</label>
            <div class="select-wrapper">
                <select id="ssid" name="ssid" required>
                    <option disabled selected>Netzwerke werden geladen...</option>
                </select>
                <svg class="select-icon" viewBox="0 0 24 24" aria-hidden="true">
                    <path fill="currentColor" d="M7 10l5 5 5-5z" />
                </svg>
            </div>
        <div class="loading" id="status"></div>

        <label for="pass">Passwort</label>
        <input type="password" id="pass" name="pass" required autocomplete="new-password">

        <button type="submit">Speichern &amp; Verbinden</button>
        </form>
    </div>
    <p>ESP32 C6 - {{IP}} ({{MAC}})</p>
    <script>
        const savedSSID = ")rawliteral";

        const char AP_HTML_SCRIPT[] PROGMEM = R"rawliteral(";
        fetch("/wifis")
        .then(response => response.json())
        .then(data => {
            const ssidSelect = document.getElementById("ssid");
            ssidSelect.innerHTML = "";
            data.forEach(ssid => {
                const option = document.createElement("option");
                option.value = ssid;
                option.textContent = ssid;
                if (ssid === savedSSID) {
                    option.selected = true;
                }
                ssidSelect.appendChild(option);
            });
        })
        .catch(() => {
            document.getElementById("status").textContent = "⚠️ Fehler beim Laden der Netzwerke!";
        });
    </script>
</body>
</html>
)rawliteral";