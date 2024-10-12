import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    # Add new birthday
    if request.method == "POST":

        # Access the form data
        day = request.form.get("day")
        month = request.form.get("month")
        name = request.form.get("name")

        # Check for missing values
        if not day or not month or not name:
            return redirect("/")

        # Check for correct data type
        try:
            day = int(day)
            month = int(month)
        except:
            return redirect("/")

        # Check for valid date values
        if day < 1 or day > 31 or month < 1 or month > 12:
            return redirect("/")

        # Add new entry to the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)
        return redirect("/")

    # Display existing birthdays
    else:
        birthdays = db.execute("SELECT * FROM birthdays;")
        return render_template("index.html", birthdays=birthdays)


@app.route("/delete", methods=["POST"])
def delete():
    if request.method == "POST":
        id = request.form.get("id")
        if id:
            db.execute("DELETE FROM birthdays WHERE id = ?", id)

    return redirect("/")
