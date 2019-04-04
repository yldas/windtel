from flask import jsonify
from dao.experiment import ExperimentDAO

class ExperimentHandler:

    def build_experiment_dict(self, row):
        result = {}
        result['eid'] = row[0]
        result['ename'] = row[1]
        result['edescription'] = row[2]
        result['etime'] = row[3]
        result['edate'] = row[4]
        return result

    def build_experiment_attributes(self, eid, ename, edescription, etime, edate):
        result = {}
        result['eid'] = eid
        result['ename'] = ename
        result['edescription'] = edescription
        result['etime'] = etime
        result['edate'] = edate
        return result

    def build_measurement_dict(self, row):
        result = {}
        result['mid'] = row[0]
        result['upforce'] = row[1]
        result['frontforce'] = row[2]
        result['backforce'] = row[3]
        result['leftforce'] = row[4]
        result['rightforce'] = row[5]
        result['windspeed'] = row[6]
        result['temperature'] = row[7]
        result['humidity'] = row[8]
        return result

    def build_measurement_attributes(self, mid, upforce, frontforce, backforce, leftforce, rightforce, windspeed,
                                     temperature, humidity):
        result = {}
        result['mid'] = mid
        result['upforce'] = upforce
        result['frontforce'] = frontforce
        result['backforce'] = backforce
        result['leftforce'] = leftforce
        result['rightforce'] = rightforce
        result['windspeed'] = windspeed
        result['temperature'] = temperature
        result['humidity'] = humidity
        return result

    def getAllExperiments(self):
        dao = ExperimentDAO()
        experiment_list = dao.getAllExperiments()
        result_map = []
        for row in experiment_list:
            result = self.build_experiment_dict(row)
            result_map.append(result)
        return jsonify(Experiments=result_map)

    def getExperimentInformationById(self, experimentid):
        dao = ExperimentDAO()
        result = dao.getExperimentInformationById(experimentid)
        if result is None:
            return jsonify(Error="Experiment doesn't exist!")
        else:
            result_map = self.build_experiment_dict(result)
        return jsonify(Users=result_map)

    def deleteExperimentById(self, experimentid):
        dao = ExperimentDAO()
        if not dao.getExperimentInformationById(experimentid):
            return jsonify(Error="Experiment not found."), 404
        else:
            dao.deleteExperimentById(experimentid)
            return jsonify(DeleteStatus="OK"), 200

    def getAllMeasurementsFromExperimentById(self, experimentid):
        dao = ExperimentDAO()
        measurements_list = dao.getAllMeasurementsFromExperimentById(experimentid)
        result_map = []
        for row in measurements_list:
            result = self.build_measurement_dict(row)
            result_map.append(result)
        return jsonify(Measurements=result_map)

    def deleteAllMeasurementsFromExperimentById(self, experimentid):
        dao = ExperimentDAO()
        if not dao.getExperimentInformationById(experimentid):
            return jsonify(Error="Experiment not found."), 404
        elif not dao.getAllMeasurementsFromExperimentById(experimentid):
            return jsonify(Error="No measurements found."), 404
        else:
            dao.deleteAllMeasurementsFromExperimentById(experimentid)
            return jsonify(DeleteStatus="OK"), 200

    def updateExperimentInformationById(self, experimentid, form):
        dao = ExperimentDAO()
        if not dao.getAllExperiments():
            return jsonify(Error="No experiments found"), 404
        else:
            if len(form) != 4:
                return jsonify(Error="Malformed update request"), 400
            else:
                ename = form['ename']
                edescription = form['edescription']
                etime = form['etime']
                edate = form['edate']
                if ename and edescription and etime and edate:
                    response = dao.updateExperimentInformationById(experimentid)
                    result = self.build_experiment_attributes(experimentid, ename, edescription, etime, edate)
                    return jsonify(Experiment=result), 200
                else:
                    return jsonify(Error="Unexpected attributes in update request"), 400