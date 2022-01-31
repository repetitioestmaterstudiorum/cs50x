from cs50 import SQL
from flask import Flask, render_template, request, redirect

# ---

app = Flask(__name__)

db = SQL("sqlite:///sports.db")

SPORTS = ["Basketball", "Soccer", "Ultimate Frisbee", "Football"]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    # validate name
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="Missing name")

    # validate sports
    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message="No sport selected")
    if not sport in SPORTS:
        return render_template("error.html", message="Sport not available")
    
    # store registrant and chosen sport
    db.execute("INSERT INTO registrants (name, sport) VALUES(?, ?)", name, sport)

    # show everyone who is registered so far
    return redirect("/registrants")

@app.route("/deregister", methods=["POST"])
def deregister():
    # delete (hard core DELETE in db) registrant
    id = request.form.get("id")
    if id:
        db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)

# run with `flask run`
# create the db:
# `sqlite3 sports.db``
# `CREATE TABLE registrants (id INTEGER, name TEXT NOT NULL, sport TEXT NOT NULL, PRIMARY KEY(id));`

