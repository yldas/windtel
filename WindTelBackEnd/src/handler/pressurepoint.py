from flask import jsonify
from dao.pressurepoint import PressurePointDAO

class PressurePointHandler:

    def build_pressurepoint_dict(self, row):
        result = {}
        result['pid'] = row[0]
        result['ppoint'] = row[1]
        result['sensor_num'] = row[2]
        return result

    def build_pressurepoint_attributes(self, pid, ppoint, sensor_num):
        result = {}
        result['pid'] = pid
        result['ppoint'] = ppoint
        result['sensor_num'] = sensor_num
        return result

    def getAllPressurePoints(self):
        dao = PressurePointDAO()
        pressurepoints_list = dao.getAllPressurePoints()
        result_map = []
        for row in pressurepoints_list:
            result = self.build_pressurepoint_dict(row)
            result_map.append(result)
        return jsonify(PressurePoints=result_map)