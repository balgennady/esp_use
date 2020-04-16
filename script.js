var Socket;
function init() {
    Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
}

document.getElementById('BTN_LED').addEventListener('click', buttonClicked);
function buttonClicked() {
    var btn = document.getElementById('BTN_LED')
    var btnText = btn.textContent || btn.innerText;
    if (btnText === 'Turn on the LED') { btn.innerHTML = "Turn off the LED"; document.getElementById('LED_status').innerHTML = 'LED is on'; sendText('1'); }
    else { btn.innerHTML = "Turn on the LED"; document.getElementById('LED_status').innerHTML = 'LED is off'; sendText('0'); }
}

function sendText(data) {
    Socket.send(data);
}

window.onload = function (e) {
    init();
}