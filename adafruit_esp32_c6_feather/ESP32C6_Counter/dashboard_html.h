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
            <div class="w-full h-full">
                <div id="flipcounter" class="pointer-events-none">
                    <div class="flip-pane-2">
                        <ul class="flip flip-item flip-home list-style-none">
                            <li class="before">
                                <span>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-up">
                                        <div class="flip-text">00</div>
                                    </div>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-down">
                                        <div class="flip-text">00</div>
                                    </div>
                                </span>
                            </li>
                            <li class="active">
                                <span>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-up">
                                        <div class="flip-text">00</div>
                                    </div>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-down">
                                        <div class="flip-text">00</div>
                                    </div>
                                </span>
                            </li>
                        </ul>
                        <div class="vs-icon">
                            <svg xmlns="http://www.w3.org/2000/svg" width="96" height="96" viewBox="0 0 24 24" fill="currentColor" stroke="currentColor" stroke-width="1" stroke-linecap="round" stroke-linejoin="round"><path d="M12 12m-1 0a1 1 0 1 0 2 0a1 1 0 1 0 -2 0" /><path d="M12 5m-1 0a1 1 0 1 0 2 0a1 1 0 1 0 -2 0" /></svg>
                        </div>
                        <ul class="flip flip-item flip-guest list-style-none">
                            <li class="before">
                                <span>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-up">
                                        <div class="flip-text">00</div>
                                    </div>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-down">
                                        <div class="flip-text">00</div>
                                    </div>
                                </span>
                            </li>
                            <li class="active">
                                <span>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-up">
                                        <div class="flip-text">00</div>
                                    </div>
                                    <div class="absolute left-0 w-full z-10 overflow-hidden flip-down">
                                        <div class="flip-text">00</div>
                                    </div>
                                </span>
                            </li>
                        </ul>
                    </div>
                </div>
            </div>

            <!-- <span id="counter">0</span> -->

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
  
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/2.0.0/jquery.min.js"></script>
    <script>
        var flipClock;
        var saveHome, saveGuest,
                Home, Guest,
                flipCounterEl = $( "#flipcounter" );

        var FlipCounter = function () {
            

            function addZeros( num, no ) {
                var str   = num.toString(),
                    zero  = "",
                    len   = str.length,
                    total = no + 1;

                if ( len < total ) {
                    var zeroTotal = total - len, i;

                    for ( i = 1; i <= zeroTotal; i++ ) {
                        zero += "0";
                    }

                    str = zero + str;
                }
                return str;
            }

            function init() {
                Home = new Control( '.flip-home' );
                Guest = new Control( '.flip-guest' );

                saveHome = 0;
                saveGuest = 0;
            }

            function reset() {
                saveHome = 0;
                saveGuest = 0;

                Home.process( saveHome );
                Guest.process( saveGuest );
            }

            function addHome() {
                saveHome++;
                Home.process( saveHome );
            }

            function addGuest() {
                saveGuest++;
                Guest.process( saveGuest );
            }

            function Control( elSelector ) {
                this.el   = flipCounterEl.find( elSelector );
                this.els  = this.el.find( 'li' );
                this.curr = 0;
            }

            Control.prototype = {
                process: function( value ) {
                    var curli = this.els.filter( '.active' );

                    if ( curli.is( ":last-child" ) ) {
                        this.els.removeClass( "before" );
                        curli.addClass( "before" ).removeClass( "active" );
                        curli = this.els.eq( 0 );
                        curli.addClass( "active" );
                        this.curr = 0;
                    } else {
                        this.els.removeClass( "before" );
                        curli.addClass( "before" ).removeClass( "active" );
                        this.els.eq( 1 ).addClass( "active" );
                        this.curr = 1;
                    }

                    this.setValue( value );
                },

                setValue: function( value ) {
                    var formatedValue = addZeros( value, 1 ),
                        nextli = this.els.eq( this.curr );

                    nextli.find( ".flip-text" ).html( formatedValue );
                }
            };

            return {
                init: init,
                addHome: addHome,
                addGuest: addGuest,
                reset: reset
            }
        };

        $( document ).ready( function() {
            flipCounter = FlipCounter();
            flipCounter.init();
        });

        let gameStartEpoch = 0;
        let scoreUpdateInterval = null;

        async function updateScore() {
            const res = await fetch("/status");
            const data = await res.json();
            // document.getElementById("counter").textContent = data.scoreA + ":" + data.scoreB;

            if (data.scoreA !== saveHome || data.scoreB !== saveGuest) {
                if (scoreUpdateInterval) {
                    clearInterval(scoreUpdateInterval);
                }
                if (saveHome !== data.scoreA) {
                    flipCounter.addHome();
                    saveHome = data.scoreA;
                }
                if (saveGuest !== data.scoreB) {
                    flipCounter.addGuest();
                    saveGuest = data.scoreB;
                }

                setTimeout(() => {
                    scoreUpdateInterval = setInterval(updateScore, 500);
                }, 5000);
            }
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
            flipCounter.reset();
            startGameClock();
        }
        async function reset() {
            await fetch("/reset");
        }
        
        function startScoreUpdates() {
            if (scoreUpdateInterval) {
                clearInterval(scoreUpdateInterval);
            }
            scoreUpdateInterval = setInterval(updateScore, 500);
        }
        
        function stopScoreUpdates() {
            if (scoreUpdateInterval) {
                clearInterval(scoreUpdateInterval);
                scoreUpdateInterval = null;
            }
        }
        
        startScoreUpdates();
        startGameClock();
    </script>
</body>
</html>
)rawliteral";