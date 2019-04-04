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

    def getAllExperiments(self):
        dao = ExperimentDAO()
        experiment_list = dao.getAllExperiments()
        result_map = []
        for row in experiment_list:
            result = self.build_experiment_dict(row)
            result_map.append(result)
        return jsonify(Experiments=result_map)