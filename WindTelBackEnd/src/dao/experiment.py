from config.dbconfig import pg_config
import psycopg2
from flask import jsonify

class ExperimentDAO:

    # def __init__(self):
    #     connection_url = "dbname=%s user=%s" % (pg_config['dbname'], pg_config['user'], pg_config['password'])
    #     self.conn = psycopg2.connect(connection_url)

    def getAllExperiments(self):
        result = [[1, 'Test Experiment', 'Data acquisition test', '00:00:35', '4/3/2019']]
        return result

    def getExperimentInformationById(self, experimentid):
        result = [1, 'Test Experiment', 'Data acquisition test', '00:00:35', '4/3/2019']
        return result

    def getAllMeasurementsFromExperimentById(self, experimentid):
        result = [[1, 12.8, 33.4, 0.97, 16.4, 1.23, 22, 78.4, 63]]
        return result

    def deleteAllMeasurementsFromExperimentById(self, experimentid):
        result = [[1, 12.8, 33.4, 0.97, 16.4, 1.23, 22, 78.4, 63]]
        return result

    def updateExperimentInformationById(self, experimentid):
        result = []
        return result

    def deleteExperimentById(self, experimentid):
        result = []
        return result