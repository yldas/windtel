from config.dbconfig import pg_config
import psycopg2
from flask import jsonify

class ExperimentDAO:

    conn = psycopg2.connect(host='127.0.0.1', database='WindTelDB',user='kahlil', password='password')

    def getAllExperiments(self):
        cursor = self.conn.cursor()
        query = "select * from experiment;"
        cursor.execute(query)
        result = []
        for row in cursor:
            result.append(row)
        return result

    def getExperimentInformationById(self, experimentid):
        cursor = self.conn.cursor()
        query = "select * from experiment where eid=%s;"
        cursor.execute(query, (experimentid,))
        result = cursor.fetchone()
        return result

    def getAllMeasurementsFromExperimentById(self, experimentid):
        cursor = self.conn.cursor()
        query = "select * from measurement where eid = %s;"
        cursor.execute(query, (experimentid,))
        result = []
        for row in cursor:
            result.append(row)
        return result

    def getAllPressurePointsFromExperimentById(self, experimentid):
        cursor = self.conn.cursor()
        query = "select * from pressurepoint where mid = (select mid from measurement where eid = %s;);"
        cursor.execute(query, (experimentid,))
        result = []
        for row in cursor:
            result.append(row)
        return result

    def getAllPressurePointsFromMeasurementById(self, experimentid):
        cursor = self.conn.cursor()
        query = "select * from pressurepoint where mid = (select mid from measurement where eid = %s);"
        cursor.execute(query, (experimentid,))
        result = []
        for row in cursor:
            result.append(row)
        return result

    def deleteAllPressurePointsFromMeasurementById(self, experimentid):
        cursor = self.conn.cursor()
        query = "delete from pressurepoint where mid = (select mid from measurement where eid = %s);"
        cursor.execute(query, (experimentid,))
        self.conn.commit()
        return

    def deleteAllMeasurementsFromExperimentById(self, experimentid):
        cursor = self.conn.cursor()
        query = "delete from measurement where eid = %s;"
        cursor.execute(query, (experimentid,))
        self.conn.commit()
        return

    def storeMeasurementFromExperimentById(self, exid, mliftforce, mdragfrontforce, mdragbackforce, mleftsideforce, mrightsideforce, mwindspeed, mtemperature, mhumidity):
        cursor = self.conn.cursor()
        query = "insert into measurement(eid, liftforce, dragfrontforce, dragbackforce, leftsideforce, rightsideforce, windspeed, \
                    temperature, humidity) values (%s, %s, %s, %s, %s, %s, %s, %s, %s) returning mid;"
        cursor.execute(query, (exid, mliftforce, mdragfrontforce, mdragbackforce, mleftsideforce, mrightsideforce, mwindspeed, mtemperature, mhumidity,))
        mid = cursor.fetchone()[0]
        self.conn.commit()
        return mid

    def deleteExperimentById(self, experimentid):
        cursor = self.conn.cursor()
        query = "delete from experiment where eid=%s;"
        cursor.execute(query, (experimentid,))
        self.conn.commit()
        return