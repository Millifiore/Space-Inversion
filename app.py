# app.py - by Isa Bolling
import flask, os
 
#FLASK
app = flask.Flask(__name__)

@app.route('/')  
def index(): 
    return flask.render_template("SpaceInversion.html")

@app.route('/SpaceInversion.js')
def mario_js():
    return app.send_static_file('SpaceInversion.js')

@app.route('/SpaceInversion.js.mem')
def mario_mem():
    return app.send_static_file('SpaceInversion.js.mem')

@app.route('/SpaceInversion.data')
def mario_data():
    return app.send_static_file('SpaceInversion.data')

@app.route('/SpaceInversion.wasm')
def mario_wasm():
    return app.send_static_file('SpaceInversion.wasm')

app.run(
    port=int(os.getenv('PORT', 8080)),
    host=os.getenv('IP', '0.0.0.0'),
    debug=True
)
