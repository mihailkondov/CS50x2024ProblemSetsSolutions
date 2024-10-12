from flask import Flask, render_template, request, redirect

app = Flask(__name__)

REGISTRANTS = {}
SPORTS = ["Basketball", "Soccer", "Ultimate frisbee"]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():

    # Validate name
    name = request.form.get("name")
    if not name:
        return render_template("failure.html")

    # Validate sport
    sport = request.form.get("sport")
    if not sport:
        return render_template("failure.html")

    if sport not in SPORTS:
        return render_template("failure.html")

    # Remember registrant
    REGISTRANTS[name] = sport

    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)
