from flask import Flask, render_template, request

# ---


app = Flask(__name__)


SPORTS = ["Basketball", "Soccer", "Ultimate Frisbee", "Football"]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():
    # validate input
    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("failure.html")
    # confirm registration
    return render_template("success.html")


# @app.route("/greet", methods=["POST"])
# def greet():
#     name = request.form.get("name") or "nameless person"
#     return render_template("greet.html", name=name)


# run this with `flask run` in this directory
