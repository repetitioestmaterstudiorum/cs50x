from flask import Flask, render_template, request

# ---


# run this with `flask run` in this directory
app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get("name")
    return render_template("greet.html", name=name)
