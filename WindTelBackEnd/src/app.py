from flask import Flask, jsonify, request
from handler.researcher import ResearcherHandler
from handler.experiment import ExperimentHandler
from handler.measurement import MeasurementHandler
from handler.pressurepoint import PressurePointHandler
from flask_cors import CORS

#Activate
app = Flask(__name__)
CORS(app)

# Default route - done
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

#Get all users
@app.route('/WindTel/users/')
def getAllUsers():
    return ResearcherHandler().getAllUsers()

#Get user information by id, update user information or delete the user - done
@app.route('/WindTel/users/<int:userid>/', methods=['GET', 'DELETE'])
def getUserInformationById(userid):
    if request.method == 'DELETE':
        return ResearcherHandler().deleteUserById(userid)
    else:
        return ResearcherHandler().getUserInformationById(userid)

#View user profile - done
@app.route('/WindTel/users/<int:userid>/profile/', methods=['GET', 'PUT'])
def getUserProfileById(userid):
    if request.method == 'PUT':
        return ResearcherHandler().updateUserProfileById(userid, request.json)
    else:
        return ResearcherHandler().getUserProfileById(userid)

#Get experiments from a user by id or delete them - done
@app.route('/WindTel/users/<int:userid>/experiments/', methods=['GET', 'DELETE', 'POST'])
def getAllExperimentsFromUserById(userid):
    if request.method == 'DELETE':
        return ResearcherHandler().deleteAllExperimentsFromUserById(userid)
    elif request.method == 'POST':
        return ResearcherHandler().storeExperimentFromUserById(userid, request.json)
    else:
        return ResearcherHandler().getAllExperimentsFromUserById(userid)

#Get experiment from a user by id, update it, or delete it - done
@app.route('/WindTel/users/<int:userid>/experiments/<int:experimentid>/', methods=['GET','DELETE','PUT'])
def getExperimentFromUserById(userid, experimentid):
    if request.method == 'DELETE':
        return ResearcherHandler().deleteExperimentFromUserById(userid, experimentid)
    elif request.method == 'PUT':
        return ResearcherHandler().updateExperimentInformationById(userid, experimentid, request.json)
    else:
        return ResearcherHandler().getExperimentFromUserById(userid, experimentid)

#Get all experiments - done
@app.route('/WindTel/experiments/')
def getAllExperiments():
    return ExperimentHandler().getAllExperiments()

#Get experiment by id or delete them - done
@app.route('/WindTel/experiments/<int:experimentid>/', methods=['GET', 'DELETE', 'PUT'])
def getExperimentInformationById(experimentid):
    if request.method == 'DELETE':
        return ExperimentHandler().deleteExperimentById(experimentid)
    else:
        return ExperimentHandler().getExperimentInformationById(experimentid)

#Get measurements of an experiment by id, update it, or delete them - done
@app.route('/WindTel/experiments/<int:experimentid>/measurements/', methods=['GET', 'DELETE', 'POST'])
def getMeasurementsFromExperimentById(experimentid):
    if request.method == 'DELETE':
        return ExperimentHandler().deleteAllMeasurementsFromExperimentById(experimentid)
    elif request.method == 'POST':
        return ExperimentHandler().storeMeasurementFromExperimentById(experimentid, request.json)
    else:
        return ExperimentHandler().getAllMeasurementsFromExperimentById(experimentid)

#Get all measurements obtained in the system - done
@app.route('/WindTel/measurements/')
def getAllMeasurements():
    return MeasurementHandler().getAllMeasurements()

#Get measurement by id - done
@app.route('/WindTel/measurements/<int:measurementid>/', methods=['GET', 'DELETE'])
def getMeasurementById(measurementid):
    if request.method == 'DELETE':
        return MeasurementHandler().deleteMeasurementById(measurementid)
    else:
        return MeasurementHandler().getMeasurementById(measurementid)

#Get all pressure point measurements by id - done
@app.route('/WindTel/measurements/<int:measurementid>/pressurepoints/', methods=['GET', 'DELETE', 'POST'])
def getPressurePointsById(measurementid):
    if request.method == 'DELETE':
        return PressurePointHandler().deleteAllPressurePointsById(measurementid)
    elif request.method == 'POST':
        return PressurePointHandler().storePressurePointById(measurementid, request.json)
    else:
        return PressurePointHandler().getPressurePointsById(measurementid)

#Get all pressure point measurements - done
@app.route('/WindTel/pressurepoints/', methods=['GET', 'DELETE'])
def getAllPressurePoints():
    if request.method == 'DELETE':
        return PressurePointHandler().deleteAllPressurePoints()
    else:
        return PressurePointHandler().getAllPressurePoints()

#Get pressure point by id - done
@app.route('/WindTel/pressurepoints/<int:pressurepointid>/', methods=['GET', 'DELETE'])
def getPressurePointById(pressurepointid):
    if request.method == 'DELETE':
        return PressurePointHandler().deletePressurePointById(pressurepointid)
    else:
        return PressurePointHandler().getPressurePointById(pressurepointid)

if __name__ == '__main__':
    app.run(debug=True)