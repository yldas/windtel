from flask import jsonify
from dao.measurement import MeasurementDAO

class MeasurementHandler:

    def build_measurement_dict(self, row):
        result = {}
        result['eid'] = row[0]
        result['mid'] = row[1]
        result['upforce'] = row[2]
        result['frontforce'] = row[3]
        result['backforce'] = row[4]
        result['leftforce'] = row[5]
        result['rightforce'] = row[6]
        result['windspeed'] = row[7]
        result['temperature'] = row[8]
        result['humidity'] = row[9]
        return result

    def build_measurement_attributes(self, eid, mid, upforce, frontforce, backforce, leftforce, rightforce, windspeed, temperature, humidity):
        result = {}
        result['eid'] = eid
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

    def getAllMeasurements(self):
        dao = MeasurementDAO()
        measurement_list = dao.getAllMeasurements()
        result_map = []
        for row in measurement_list:
            result = self.build_measurement_dict(row)
            result_map.append(result)
        return jsonify(Measurements=result_map)

    def getMeasurementById(self, measurementid):
        dao = MeasurementDAO()
        result = dao.getMeasurementById(measurementid)
        if result is None:
            return jsonify(Error="Measurement doesn't exist!")
        else:
            result_map = self.build_measurement_dict(result)
        return jsonify(Users=result_map)

    def deleteMeasurementById(self, measurementid):
        dao = MeasurementDAO()
        if not dao.getMeasurementById(measurementid):
            return jsonify(Error="Measurement not found."), 404
        else:
            if dao.getPressurePointsFromMeasurementById(measurementid):
                dao.deletePressurePointsFromMeasurementById(measurementid)
            if dao.getMeasurementById(measurementid):
                dao.deleteMeasurementById(measurementid)
            return jsonify(DeleteStatus="OK"), 200