from flask import jsonify
from dao.measurement import MeasurementDAO

class MeasurementHandler:

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

    def build_measurement_attributes(self, mid, upforce, frontforce, backforce, leftforce, rightforce, windspeed, temperature, humidity):
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

    def getAllMeasurements(self):
        dao = MeasurementDAO()
        measurement_list = dao.getAllMeasurements()
        result_map = []
        for row in measurement_list:
            result = self.build_measurement_dict(row)
            result_map.append(result)
        return jsonify(Measurements=result_map)