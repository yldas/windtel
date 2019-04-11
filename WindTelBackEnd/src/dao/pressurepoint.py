from config.dbconfig import pg_config
import psycopg2
from flask import jsonify

class PressurePointDAO:

    conn = psycopg2.connect(host='127.0.0.1', database='WindTelDB',user='kahlil', password='password')

    def getAllPressurePoints(self):
        cursor = self.conn.cursor()
        query = "select * from pressurepoint;"
        cursor.execute(query)
        result = []
        for row in cursor:
            result.append(row)
        return result

    def deleteAllPressurePoints(self):
        cursor = self.conn.cursor()
        query = "delete from pressurepoint;"
        cursor.execute(query)
        self.conn.commit()
        return

    def getPressurePointById(self, pressurepointid):
        cursor = self.conn.cursor()
        query = "select * from pressurepoint where pid=%s;"
        cursor.execute(query, (pressurepointid,))
        result = cursor.fetchone()
        return result

    def deletePressurePointById(self, pressurepointid):
        cursor = self.conn.cursor()
        query = "delete from pressurepoint where pid = %s;"
        cursor.execute(query, (pressurepointid,))
        self.conn.commit()
        return

    def getPressurePointsById(self, measurementid):
        cursor = self.conn.cursor()
        query = "select * from pressurepoint where mid = %s;"
        cursor.execute(query, (measurementid,))
        result = []
        for row in cursor:
            result.append(row)
        return result

    def storePressurePointById(self, measurementid, prpoint, psensor_num):
        cursor = self.conn.cursor()
        query = "insert into pressurepoint(mid, ppoint, sensor_num) values (%s, %s, %s) returning pid;"
        cursor.execute(query, (measurementid, prpoint, psensor_num,))
        pid = cursor.fetchone()[0]
        self.conn.commit()
        return pid

    def deletePressurePointsById(self, measurementid):
        cursor = self.conn.cursor()
        query = "delete from pressurepoint where mid = %s;"
        cursor.execute(query, (measurementid,))
        self.conn.commit()
        return