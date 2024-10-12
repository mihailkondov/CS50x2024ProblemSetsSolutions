from flask import Flask, render_template, request

app = Flask(__name__) #__name__ is a special variable name in Python that returns the current file's name

# 1 - 5
# @app.route("/")
# def index():
#     # return "hello, world" #1
#     # return render_template("index.html") #2

#     # 3:
#     # if "name" in request.args:
#     #     name = request.args["name"] # args is a dictionary that comes with Flask and puts KVP from the user in python dictionary
#     # else:
#     #     name = "world"
#     # return render_template("index.html", placeholder=name) #name is a Python variable, placeholder is a Jinja variable (from index.html)

#     # # 3.2
#     # name = request.args.get("name", "world") # this gets value by given key or a given second argument "world"
#     #                                          # if such key was not found. If no argument is specified
#     #                                          # None is given as argument by default.

#     # return render_template("index.html", placeholder=name)

#     #3.3
#     # names of the variables in pyton and jinja can and sometimes should be the same:
#     # name = request.args.get("name", "world") # this gets value by given key or a given second argument "world"
#     #                                          # if such key was not found. If no argument is specified
#     #                                          # None is given as argument by default.

#     # return render_template("index.html", name=name)

#     # 4
#     return render_template("index.html")

# 4
# @app.route("/greet")
# def greet():
#     name = request.args.get("name", "world")
#     return render_template("greet.html", name=name)


# # 5 using the post method:
# @app.route("/greet", methods=["POST"])
# def greet():
#     name = request.form.get("name", "world")
#     return render_template("greet.html", name=name)

# 6 consolidating related functionality on the same route
@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name", "world")
        return render_template("greet.html", name=name)
    else:
        return render_template("index.html")

