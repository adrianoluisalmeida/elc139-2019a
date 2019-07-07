var i = 0;

function timedCount() {
    i = i + 1;
    postMessage(i); // Envia o dado para o objeto de worker que iniciou
                    // essa threads
    setTimeout(timedCount(),10000);
}

timedCount();