from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    stocks = db.execute("SELECT symbol, SUM(shares), price FROM transactions WHERE buyerid = :id GROUP BY symbol HAVING SUM(shares) > 0;", id=session["user_id"])
    currentcash = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    totalcash = currentcash[0]["cash"]
    currentcash = usd(currentcash[0]["cash"])

    for stock in stocks:
        price = lookup(stock["symbol"])

        if not price:
            stock["price"] = 0

        stock["total"] = stock["price"] * stock["SUM(shares)"]
        totalcash += stock["total"]
        stock["total"] = usd(stock["total"])
        stock["price"] = usd(price["price"])

    totalcash = usd(totalcash)

    return render_template("index.html", stocks=stocks, cash=currentcash, total=totalcash)
    # return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide valid stock name", 400)

        try:
            n = float(request.form.get("shares"))
        except ValueError:
            return apology("must provide valid number", 400)

        if not float(request.form.get("shares")).is_integer() or not float(request.form.get("shares")) > 0:
            return apology("must provide valid number", 400)

        result = lookup(request.form.get("symbol"))

        if not result:
            return apology("something went wrong", 400)

        else:
            currentcash = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
            currentcash = currentcash[0]["cash"]
            needcash = result["price"] * int(float(request.form.get("shares")))

            if currentcash < needcash:
                return render_template("test.html", result0="Current cash: "+usd(currentcash), result1="Needed cash: "+usd(needcash))
            else:
                addtrans = db.execute("INSERT INTO transactions (symbol, price, shares, buyerid) VALUES (:symbol, :price, :shares, :buyerid)", symbol=result["symbol"], price=result["price"], shares=int(float(request.form.get("shares"))), buyerid=session["user_id"])
                updcash = db.execute("UPDATE users SET cash = cash - :needcash WHERE id = :id", needcash=needcash, id=session["user_id"])
                return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    stocks = db.execute("SELECT timestamp, symbol, price, shares FROM transactions WHERE buyerid = :id", id=session["user_id"])

    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide valid stock name", 400)

        result = lookup(request.form.get("symbol"))

        if not result:
            return apology("something went wrong", 400)

        return render_template("quoted.html", result=result["name"] + " (" + result["symbol"] + ") current price is " + usd(result["price"]))

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
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

        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("must provide matching passwords", 400)

        pass_hash = generate_password_hash(request.form.get("password"))

        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=pass_hash)

        if not result:
            return apology("username already exists", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    stocks = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE buyerid = :id GROUP BY symbol HAVING SUM(shares) > 0;", id=session["user_id"])

    output = ""

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("Select stock!", 400)

        try:
            n = float(request.form.get("shares"))
        except ValueError:
            return apology("must provide valid number", 400)

        if not float(request.form.get("shares")).is_integer() or not float(request.form.get("shares")) > 0:
            return apology("must provide valid number", 400)

        shares = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE buyerid = :id AND symbol = :symbol;",
                            id=session["user_id"], symbol=request.form.get("symbol"))

        if int(request.form.get("shares")) > shares[0]["SUM(shares)"]:
            return apology("You don't have enough amount!", 400)

        result = lookup(request.form.get("symbol"))

        if not result:
            return apology("something went wrong", 400)

        sellvalue = int(float(request.form.get("shares"))) * result["price"]
        addtrans = db.execute("INSERT INTO transactions (symbol, price, shares, buyerid) VALUES (:symbol, :price, :shares, :buyerid)",
                            symbol=request.form.get("symbol"), price=result["price"], shares=-int(float(request.form.get("shares"))), buyerid=session["user_id"])
        updcash = db.execute("UPDATE users SET cash = cash + :sellvalue WHERE id = :id",
                            sellvalue=sellvalue, id=session["user_id"])

        output = str(sellvalue)

        return redirect("/")

    return render_template("sell.html", stocks=stocks, output=output)


@app.route("/passchange", methods=["GET", "POST"])
@login_required
def passchange():

    user = db.execute("SELECT username, hash FROM users WHERE id = :id", id=session["user_id"])
    result = ""

    if request.method == "POST":

        # Ensure username was submitted
        if request.form.get("username") != user[0]["username"]:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("oldpassword"):
            return apology("must provide old password", 403)

        elif not request.form.get("newpassword"):
            return apology("must provide new password", 403)

        elif not request.form.get("confirmation"):
            return apology("must provide new password confirmation", 403)

        elif request.form.get("newpassword") != request.form.get("confirmation"):
            return apology("must provide matching passwords", 403)

        newpass_hash = generate_password_hash(request.form.get("newpassword"))

        if not check_password_hash(user[0]["hash"], request.form.get("oldpassword")):
            return apology("old pass is wrong!", 403)
        else:
            db.execute("UPDATE users SET hash = :newhash WHERE id = :id",
                        newhash=newpass_hash, id=session["user_id"])
            return render_template("passchange.html", result="PASSWORD CHANGED!", user=user)

    return render_template("passchange.html", result="", user=user)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
