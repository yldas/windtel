from flask import jsonify
from dao.pressurepoint import PressurePointDAO

class PressurePointHandler:

    def build_pressurepoint_dict(self, row):
        result = {}
        result['pid'] = row[0]
        result['ppoint'] = row[1]
        result['sensor_num'] = row[2]
        result['mid'] = row[3]
        return result

    def build_pressurepoint_attributes(self, mid, pid, ppoint, sensor_num):
        result = {}
        result['pid'] = pid
        result['ppoint'] = ppoint
        result['sensor_num'] = sensor_num
        result['mid'] = mid
        return result

    def getAllPressurePoints(self):
        dao = PressurePointDAO()
        pressurepoints_list = dao.getAllPressurePoints()
        result_map = []
        for row in pressurepoints_list:
            result = self.build_pressurepoint_dict(row)
            result_map.append(result)
        return jsonify(PressurePoints=result_map)

    def deleteAllPressurePoints(self):
        dao = PressurePointDAO()
        if not dao.getAllPressurePoints():
            return jsonify(Error="No pressure points found."), 404
        else:
            if dao.getAllPressurePoints():
                dao.deleteAllPressurePoints()
            return jsonify(DeleteStatus="OK"), 200

    def getPressurePointById(self, pressurepointid):
        dao = PressurePointDAO()
        result = dao.getPressurePointById(pressurepointid)
        if result is None:
            return jsonify(Error="Pressure point doesn't exist!")
        else:
            result_map = self.build_pressurepoint_dict(result)
        return jsonify(Users=result_map)

    def deletePressurePointById(self, pressurepointid):
        dao = PressurePointDAO()
        if not dao.getPressurePointById(pressurepointid):
            return jsonify(Error="Pressure point not found."), 404
        else:
            dao.deletePressurePointById(pressurepointid)
            return jsonify(DeleteStatus="OK"), 200

    def getPressurePointsById(self, measurementid):
        dao = PressurePointDAO()
        result = dao.getPressurePointsById(measurementid)
        if result is None:
            return jsonify(Error="Pressure point doesn't exist!")
        else:
            result_map = []
            for row in result:
                result = self.build_pressurepoint_dict(row)
                result_map.append(result)
            return jsonify(PressurePoints=result_map)

    def storePressurePointById(self, measurementid, form):
        dao = PressurePointDAO()
        if len(form) != 2:
            return jsonify(Error="Malformed post request"), 400
        else:
            mid = measurementid
            ppoint = form['ppoint']
            sensor_num = form['sensor_num']
            if ppoint and sensor_num:
                pid = dao.storePressurePointById(mid, ppoint, sensor_num)
                result = self.build_pressurepoint_attributes(pid, ppoint, sensor_num, mid)
                return jsonify(PressurePoint=result), 200
            else:
                return jsonify(Error="Unexpected attributes in post request"), 400

    def deleteAllPressurePointsById(self, measurementid):
        dao = PressurePointDAO()
        if not dao.getPressurePointsById(measurementid):
            return jsonify(Error="Pressure points not found."), 404
        else:
            dao.deletePressurePointsById(measurementid)
            return jsonify(DeleteStatus="OK"), 200