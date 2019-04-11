from flask import jsonify
from dao.experiment import ExperimentDAO

class ExperimentHandler:

    def build_experiment_dict(self, row):
        result = {}
        result['rid'] = row[0]
        result['eid'] = row[1]
        result['ename'] = row[2]
        result['edescription'] = row[3]
        result['etime'] = row[4]
        result['edate'] = row[5]
        return result

    def build_experiment_attributes(self, rid, eid, ename, edescription, etime, edate):
        result = {}
        result['rid'] = rid
        result['eid'] = eid
        result['ename'] = ename
        result['edescription'] = edescription
        result['etime'] = etime
        result['edate'] = edate
        return result

    def build_measurement_dict(self, row):
        result = {}
        result['eid'] = row[0]
        result['mid'] = row[1]
        result['liftforce'] = row[2]
        result['dragfrontforce'] = row[3]
        result['dragbackforce'] = row[4]
        result['leftsideforce'] = row[5]
        result['rightsideforce'] = row[6]
        result['windspeed'] = row[7]
        result['temperature'] = row[8]
        result['humidity'] = row[9]
        return result

    def build_measurement_attributes(self, eid, mid, liftforce, dragfrontforce, dragbackforce, leftsideforce, rightsideforce, windspeed,
                                     temperature, humidity):
        result = {}
        result['eid'] = eid
        result['mid'] = mid
        result['liftforce'] = liftforce
        result['dragfrontforce'] = dragfrontforce
        result['dragbackforce'] = dragbackforce
        result['leftsideforce'] = leftsideforce
        result['rightsideforce'] = rightsideforce
        result['windspeed'] = windspeed
        result['temperature'] = temperature
        result['humidity'] = humidity
        return result

    def getAllExperiments(self):
        dao = ExperimentDAO()
        experiment_list = dao.getAllExperiments()
        if experiment_list:
            result_map = []
            for row in experiment_list:
                result = self.build_experiment_dict(row)
                result_map.append(result)
            return jsonify(Experiments=result_map)
        else:
            return jsonify(Error="No experiments to show.")

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
            if dao.getAllPressurePointsFromMeasurementById(experimentid):
                dao.deleteAllPressurePointsFromMeasurementById(experimentid)
            if dao.getAllMeasurementsFromExperimentById(experimentid):
                dao.deleteAllMeasurementsFromExperimentById(experimentid)
            if dao.getExperimentInformationById(experimentid):
                dao.deleteExperimentById(experimentid)
            return jsonify(DeleteStatus="OK"), 200

    def storeMeasurementFromExperimentById(self, experimentid, form):
        dao = ExperimentDAO()
        if len(form) != 8:
            return jsonify(Error="Malformed post request"), 400
        else:
            eid = experimentid
            liftforce = form['liftforce']
            dragfrontforce = form['dragfrontforce']
            dragbackforce = form['dragbackforce']
            leftsideforce = form['leftsideforce']
            rightsideforce = form['rightsideforce']
            windspeed = form['windspeed']
            temperature = form['temperature']
            humidity = form['humidity']
            if eid and liftforce and dragfrontforce and dragbackforce and leftsideforce and rightsideforce and windspeed and temperature and humidity:
                mid = dao.storeMeasurementFromExperimentById(eid, liftforce, dragfrontforce, dragbackforce, leftsideforce, rightsideforce, windspeed, temperature, humidity)
                result = self.build_measurement_attributes(mid, liftforce, dragfrontforce, dragbackforce, leftsideforce, rightsideforce, windspeed, temperature, humidity, eid)
                return jsonify(Measurement=result), 200
            else:
                return jsonify(Error="Unexpected attributes in post request"), 400

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
            if dao.getAllPressurePointsFromMeasurementById(experimentid):
                dao.deleteAllPressurePointsFromMeasurementById(experimentid)
            if dao.getAllMeasurementsFromExperimentById(experimentid):
                dao.deleteAllMeasurementsFromExperimentById(experimentid)
            return jsonify(DeleteStatus="OK"), 200