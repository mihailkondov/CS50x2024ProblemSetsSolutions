function includeHTML() {
    let xhttp = new XMLHttpRequest();

    // Handle the response once the request is complete
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("menu").innerHTML = this.responseText;
        }
    };

    // Open and send the request
    xhttp.open("GET", "./menu.html", true);
    xhttp.send();
}

// Call the function to load the menu content
includeHTML();

