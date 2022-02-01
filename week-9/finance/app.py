import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # calculate data to show on page
    # get user id
    user_id = session.get("user_id")

    # get all symbols
    symbols = [s_dict["symbol"] for s_dict in db.execute("SELECT DISTINCT(symbol) FROM transactions WHERE user_id = ?", user_id)]

    # get totals (per stock: symbol, amount of shares, price, total)
    stock_totals = []
    # get db data
    for s in symbols:
        # relevant data in db
        db_data = db.execute(
            "SELECT SUM(total_price), SUM(amount) FROM transactions WHERE user_id = ? AND symbol = ?", 
            user_id, s)[0]

        buy_value = round(db_data['SUM(total_price)'], 2)
        shares = db_data['SUM(amount)']

        curr_value = round(lookup(s)["price"] * shares, 2)

        # add to dict
        stock_totals.append({
            "symbol": s, 
            "shares": shares, 
            "buy_value": buy_value, 
            "curr_value": curr_value
        })
    
    # grand total: current cash plus all stocks's totals
    current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
    total_stock_value = round(sum([st['curr_value'] for st in stock_totals]), 2)
    grand_totals = {
        "current_cash": current_cash,
        "total_stock_value": total_stock_value,
        "grand_total": round(current_cash + total_stock_value, 2)
    }

    return render_template("index.html", stock_totals=stock_totals, grand_totals=grand_totals)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # handle form submission and buy stocks
    if request.method == "POST":
        # check symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        quote = lookup(symbol)
        if not quote:
            return apology(f"symbol {symbol} not found on IEX", 400)
        
        # check shares
        shares = request.form.get("shares")
        try:
            shares_int = int(shares)
            if shares_int < 1: 
                return apology("the minimum purchase amount is 1 share!", 400)
        except ValueError:
            return apology("shares must be a natural number (1, 2, 3...)!", 400)
        
        # check sufficient funds
        total_price = round(shares_int * quote["price"], 2)
        user_id = session.get("user_id")
        user_cash = round(db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash'], 2)
        if user_cash < total_price:
            return apology(f"insufficient funds: {user_cash}, total price: {total_price}", 400)
        
        # purchase shares
        curr_timestamp = datetime.datetime.now()
        new_trans_id = db.execute("""INSERT INTO transactions
            (user_id, symbol, amount, price, total_price, timestamp, type)
            VALUES (?, ?, ?, ?, ?, ?, ?);""", user_id, quote["symbol"], shares, quote["price"], total_price, curr_timestamp, "buy")

        # update user total
        new_user_cash = round(user_cash - total_price, 2)
        user_updated = db.execute("UPDATE users SET cash = ? WHERE id = ?", new_user_cash, user_id)

        if new_trans_id and user_updated:
            # needed to remove this to pass check50, which expects to go back to "/" after buying
            # # show purchase result
            # purchase = {
            #     "symbol": quote["symbol"],
            #     "name": quote["name"],
            #     "amount": shares_int,
            #     "price": quote["price"],
            #     "total_price": total_price
            # }
            # return render_template("buy.html", purchase=purchase)
            return redirect("/")
        else:
            return apology("purchase could not be made", 400)
        
    # show form to buy stocks
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session.get("user_id")
    db_data = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)    
    transactions = []
    for d in db_data:
        datetime_obj = datetime.datetime.strptime(d['timestamp'], "%Y-%m-%d %H:%M:%S")
        print(datetime_obj)
        transactions.append({
            "date": datetime_obj.strftime("%d.%m.%Y"),
            "time": datetime_obj.strftime("%H:%M:%S"),
            "symbol": d["symbol"],
            "amount": d["amount"],
            "type": d["type"],
            "price": d["price"],
            "total_price": d["total_price"],
        })
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for user
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # show just the form to enter a stock symbol
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        quote = lookup(symbol)
        if not quote:
            return apology("symbol not found on IEX", 400)
        return render_template("quote.html", quote=quote)
    # show the quote for a stock symbol
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username and password were submitted
        username = request.form.get("username")
        pw = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        elif not pw:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide password twice", 400)
        elif confirmation != pw:
            return apology("passwords need to match!", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # check password strength
        if pw.isupper() or pw.islower() or pw.isdigit() or pw.isalpha() or len(pw) < 8:
            return apology("Your password must be min. 8 characters long, contain at least 1 digit and 1 upper and one lower case letter", 400)

        # Ensure username does not exist yet
        if len(rows) != 0:
            return apology("this username already exists!", 400)

        # save new user in db
        hash = generate_password_hash(pw)
        id = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)

        if id:
            # Redirect user to home page
            return redirect("/login")
        else:
            return apology("could not register...", 500)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # get data needed in each case
    user_id = session.get("user_id")
    symbols = [s_dict["symbol"] for s_dict in db.execute("SELECT DISTINCT(symbol) FROM transactions WHERE user_id = ?", user_id)]
    print("symbols", symbols)
    active_symbols = [s for s in symbols if db.execute(
        "SELECT SUM(total_price) FROM transactions WHERE user_id = ? AND symbol = ?", user_id, s)[0]['SUM(total_price)'] > 0]
    print("active_symbols", active_symbols)

    # show sellable stocks
    if request.method == "GET":
        return render_template("sell.html", active_symbols=active_symbols)

    # handle form submission and sell stocks
    else:
        # check symbol
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        quote = lookup(symbol)
        if not quote:
            return apology(f"symbol {symbol} not found on IEX", 400)
        
        # check shares
        shares = request.form.get("shares")
        try:
            shares_int = int(shares)
            if shares_int < 1: 
                return apology("the minimum sale amount is 1 share!", 400)
        except ValueError:
            return apology("shares must be a natural number (1, 2, 3...)!", 400)
        
        # check sufficient shares to sell
        user_shares = db.execute(
            "SELECT SUM(amount) FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)[0]['SUM(amount)']
        if user_shares < shares_int:
            return apology(f"insufficient shares: {user_shares} to sell {shares}", 400)
        
        # sell shares
        curr_timestamp = datetime.datetime.now()
        total_price = round(shares_int * quote["price"], 2)
        new_trans_id = db.execute("""INSERT INTO transactions
            (user_id, symbol, amount, price, total_price, timestamp, type)
            VALUES (?, ?, ?, ?, ?, ?, ?);""", user_id, quote["symbol"], shares_int * (- 1), quote["price"], total_price * (- 1), curr_timestamp, "sell")

        # update user total
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        new_user_cash = round(user_cash + total_price, 2)
        user_updated = db.execute("UPDATE users SET cash = ? WHERE id = ?", new_user_cash, user_id)

        if new_trans_id and user_updated:
            # needed to remove this to pass check50, which expects to go back to "/" after selling
            # # show sale result
            # sale = {
            #     "symbol": quote["symbol"],
            #     "amount": shares_int,
            #     "price": quote["price"],
            #     "total_price": total_price
            # }
            # return render_template("sell.html", active_symbols=active_symbols, sale=sale)
            return redirect("/")
        else:
            return apology("sale could not be made", 400)


# db schema:
# CREATE TABLE users (id INTEGER, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00, PRIMARY KEY(id));
# CREATE UNIQUE INDEX username ON users (username);
# CREATE UNIQUE INDEX id ON users (id);
# CREATE TABLE transactions (
#     id INTEGER,
#     user_id INTEGER NOT NULL,
#     symbol TEXT NOT NULL,
#     amount NUMERIC NOT NULL,
#     price NUMERIC NOT NULL,
#     total_price NUMERIC NOT NULL,
#     timestamp TIMESTAMP NOT NULL,
#     type TEXT NOT NULL,
#     PRIMARY KEY(id),
#     FOREIGN KEY(user_id) REFERENCES users(id)
# );
# CREATE INDEX user_id ON transactions (user_id);
# CREATE INDEX symbol ON transactions (symbol);

# run: `export API_KEY=..........` then `flask run`
# check: `check50 cs50/problems/2022/x/finance`
# submit: `submit50 cs50/problems/2022/x/finance`