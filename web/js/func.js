function showMessage(from, text) {
    // 没有传入text
    text = text || 'no text given.';
}

function askSure(question, yes, no) {
    if (confirm(question)) // confirm会返回true
        yes();
    else 
        no();
}
askSure("Yes | No", 
    function() {alert("yes");},
    function() {alert("no");}
)