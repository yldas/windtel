from flask import Flask, jsonify, request
from handler.researcher import ResearcherHandler
from flask_cors import CORS

#Activate
app = Flask(__name__)
CORS(app)

# Default route
@app.route('/')
@app.route('/WindTel/')
def greeting():
    return 'This is the opening page of the WindTel application'

#Registration
@app.route('/WindTel/register/', methods=['GET', 'POST'])
def registerResearcher():
    if request.method == 'POST':
        print("REQUEST: ", request.json)
        return ResearcherHandler().registerResearcher(request.json)
    else:
        return jsonify(Error="Method not allowed."), 405

#Login
@app.route('/WindTel/login/', methods=['GET', 'POST'])
def loginResearcher():
    if request.method == 'POST':
        return ResearcherHandler().loginResearcher(request.json)
    else:
        return jsonify(Error="Method not allowed."), 405

#All users
@app.route('/WindTel/users')
def getAllUsers():
    return ResearcherHandler().getAllUsers()

if __name__ == '__main__':
    app.run(debug=True)