#!/usr/bin/env python3
# app.py - by Isa Bolling
import flask, os
 
#FLASK
app = flask.Flask(__name__)

@app.route('/')  
def index(): 
    return flask.render_template("SpaceInversion.html")

@app.route('/SpaceInversion.js')
def si_js():
    return app.send_static_file('SpaceInversion.js')

@app.route('/SpaceInversion.js.mem')
def si_mem():
    return app.send_static_file('SpaceInversion.js.mem')

@app.route('/SpaceInversion.data')
def si_data():
    return app.send_static_file('SpaceInversion.data')

@app.route('/SpaceInversion.wasm')
def si_wasm():
    return app.send_static_file('SpaceInversion.wasm')

@app.route('/SpaceInversion.wast')
def si_wasm_wast():
    return app.send_static_file('SpaceInversion.wast')

@app.route('/SpaceInversion.wasm.map')
def si_wasm_map():
    return app.send_static_file('SpaceInversion.wasm.map')

@app.route('/SpaceInversion.js.map')
def si_js_map():
    return app.send_static_file('SpaceInversion.js.map')

app.run(
    port=int(os.getenv('PORT', 8080)),
    host=os.getenv('IP', '0.0.0.0'),
    debug=True
)
