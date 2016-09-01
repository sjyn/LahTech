function onSubmitPressed(){
    var upper = parseInt(document.getElementById('upper-input').value);
    var lower = parseInt(document.getElementById('lower-input').value);

    var val = Math.random() * (upper - lower + 1);
    val += lower;

    document.getElementById('result-field').innerHTML = val;
}
