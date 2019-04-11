from config.dbconfig import pg_config
import psycopg2
from flask import jsonify

class MeasurementDAO:

    conn = psycopg2.connect(host='127.0.0.1', database='WindTelDB',user='kahlil', password='password')

    def getAllMeasurements(self):
        cursor = self.conn.cursor()
        query = "select * from measurement;"
        cursor.execute(query)
        result = []
        for row in cursor:
            result.append(row)
        return result

    def getMeasurementById(self, measurementid):
        cursor = self.conn.cursor()
        query = "select * from measurement where mid=%s;"
        cursor.execute(query, (measurementid,))
        result = cursor.fetchone()
        return result

    def deleteMeasurementById(self, measurementid):
        cursor = self.conn.cursor()
        query = "delete from measurement where mid=%s;"
        cursor.execute(query, (measurementid,))
        self.conn.commit()
        return

    def getPressurePointsFromMeasurementById(self, measurementid):
        cursor = self.conn.cursor()
        query = "select * from pressurepoint where mid=%s;"
        cursor.execute(query, (measurementid,))
        result = cursor.fetchone()
        self.conn.commit()
        return result

    def deletePressurePointsFromMeasurementById(self, measurementid):
        cursor = self.conn.cursor()
        query = "delete from pressurepoint where mid=%s;"
        cursor.execute(query, (measurementid,))
        self.conn.commit()
        return