var globalMap = {};
var madlib = "";

/**
* loads the file at the given filename (relative to the caller)
*
* filename -- the name of the file
* onFileReady -- a callback that's passed the contents of the file when the read is finished
* onFileErr -- a callback that's called when an error occurs
*/
function loadFileAt(filename, onFileReady, onFileErr) {
    var fileHandle = new XMLHttpRequest();
    fileHandle.open("GET", filename, false);
    fileHandle.onreadystatechange = function(){
        if(fileHandle.readyState === 4){
            if(fileHandle.status === 200 || fileHandle.status === 0){
                onFileReady(fileHandle.responseText);
            } else {
                onFileErr();
            }
        }
    }
    fileHandle.send(null);
}

/**
* loads a random madlib
*
* return -- the string contents of the madlib
*/
function getRandomMadlib(){
    var madlibs = ["madlib_01.txt","madlib_02.txt","madlib_03.txt","madlib_04.txt"];
    var random = Math.floor(Math.random() * madlibs.length);

    var chosenMadlib = "./mlibs/" + madlibs[random];
    globalMap = {};
    document.getElementById('madlib_table').innerHTML = "";
    // var chosenMadlib = "./mlibs/madlib_01.txt";

    loadFileAt(chosenMadlib, parseMadLib, function(){
        console.log("error :(");
    });
}

/**
* parses the madlib and poplates the DOM with the appropriate fields
*
* ml -- The raw madlib content
*/
function parseMadLib(ml){
    madlib = ml;
    var table = document.getElementById('madlib_table');
    var madlibVarsRx = /\$[a-zA-Z0-9_ ']*\$\$/g;
    var madlibFields = madlib.match(madlibVarsRx);
    var rowCount = 0;
    madlibFields.forEach(function(currentValue, index, array){
        var fieldName = currentValue.substring(1, currentValue.length - 5);
        var fieldID = currentValue.substring(currentValue.length - 4, currentValue.length -2);
        if(!(fieldID in globalMap)){
            var row = table.insertRow(rowCount++);
            var cell1 = row.insertCell(0);
            var cell2 = row.insertCell(1);
            globalMap[fieldID] = "";
            cell1.innerHTML = "<p style='margin:0px; padding:0px;'>" + fieldName + ":</p>";
            cell2.innerHTML = "<input type='text' id='" + fieldID + "'/>"
        }
    });
}

/**
* called upon pressing the submit button
*/
function onSubmitPressed(){
    var resContainer = document.getElementById('res_text');

    for(var id in globalMap){
        var input = document.getElementById(id);
        var val = "<b>" + input.value + "</b>";
        var newReg = new RegExp("\\$[a-zA-Z_ ']*" + id + "\\$\\$","g");
        madlib = madlib.replace(newReg, val);
    }

    resContainer.innerHTML = madlib;
}
