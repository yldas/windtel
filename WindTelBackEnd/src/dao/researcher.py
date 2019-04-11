from config.dbconfig import pg_config
import psycopg2
from flask import jsonify

class ResearcherDAO:

    conn = psycopg2.connect(host='127.0.0.1', database='WindTelDB',user='kahlil', password='password')

    def registerResearcher(self, rename, relast_name, reemail, repassword, revocation, redepartment, reinstitution, recity):
        cursor = self.conn.cursor()
        query = "insert into researcher(rname, rlast_name, remail, rvocation, rdepartment, rinstitution, rcity, \
                    rpassword) values (%s, %s, %s, %s, %s, %s, %s, %s);"
        cursor.execute(query, (rename, relast_name, reemail, revocation, redepartment, reinstitution, recity, repassword,))
        self.conn.commit()
        return

    def loginResearcher(self, remail, rpassword):
        cursor = self.conn.cursor()
        query = "select * from researcher where remail = %s and rpassword = %s"
        cursor.execute(query, (remail, rpassword,))
        result = cursor.fetchone()
        return result

    def getAllUsers(self):
        cursor = self.conn.cursor()
        query = "select rid, rname, rlast_name, remail, rvocation, rdepartment, rinstitution, rcity from \
                researcher;"
        cursor.execute(query)
        result = []
        for row in cursor:
            result.append(row)
        return result

    def getUserInformationById(self, userid):
        cursor = self.conn.cursor()
        query = "select rid, rname, rlast_name, remail, rvocation, rdepartment, rinstitution, rcity from\
                researcher where rid=%s;"
        cursor.execute(query, (userid,))
        result = cursor.fetchone()
        return result

    def deleteUserById(self, userid):
        cursor = self.conn.cursor()
        query = "delete from researcher where rid=%s;"
        cursor.execute(query, (userid,))
        self.conn.commit()
        return

    def updateUserProfileById(self, userid, rename, relast_name, reemail, repassword, revocation, redepartment, reinstitution, recity):
        cursor = self.conn.cursor()
        query = "update researcher set rname = %s, rlast_name = %s, remail = %s, rpassword = %s, rvocation = %s, \
                rdepartment = %s, rinstitution = %s, rcity = %s where rid = %s;"
        cursor.execute(query, (rename, relast_name, reemail, revocation, redepartment, reinstitution, recity, \
                               repassword, userid))
        self.conn.commit()
        return

    def getUserProfileById(self, userid):
        cursor = self.conn.cursor()
        query = "select * from researcher where rid=%s;"
        cursor.execute(query, (userid,))
        result = cursor.fetchone()
        return result

    def getAllExperimentsFromUserById(self, userid):
        cursor = self.conn.cursor()
        query = "select * from experiment where rid = %s;"
        cursor.execute(query, (userid,))
        result = []
        for row in cursor:
            result.append(row)
        return result

    def storeExperimentFromUserById(self, reid, exname, exdescription, extime, exdate):
        cursor = self.conn.cursor()
        query = "insert into experiment(rid, ename, edescription, etime, edate) values (%s, %s, %s, %s, %s) returning eid;"
        cursor.execute(query, (reid, exname, exdescription, extime, exdate,))
        eid = cursor.fetchone()[0]
        self.conn.commit()
        return eid

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
        query = "delete from pressurepoint where mid = (select mid from measurement where eid = %s;);"
        cursor.execute(query, (experimentid,))
        self.conn.commit()
        return

    def getAllMeasurementsFromExperimentById(self, experimentid):
        cursor = self.conn.cursor()
        query = "select * from measurement where eid = %s;"
        cursor.execute(query, (experimentid,))
        result = []
        for row in cursor:
            result.append(row)
        return result

    def deleteAllMeasurementsFromExperimentById(self, experimentid):
        cursor = self.conn.cursor()
        query = "delete from measurement where eid = %s;"
        cursor.execute(query, (experimentid,))
        self.conn.commit()
        return

    def getExperimentFromUserById(self, userid, experimentid):
        cursor = self.conn.cursor()
        query = "select * from experiment where rid = %s and eid = %s;"
        cursor.execute(query, (userid, experimentid,))
        result = cursor.fetchone()
        return result

    def deleteExperimentFromUserById(self, userid, experimentid):
        cursor = self.conn.cursor()
        query = "delete from experiment where rid = %s and eid = %s;"
        cursor.execute(query, (userid, experimentid,))
        self.conn.commit()
        return

    def updateExperimentInformationById(self, userid, experimentid, ename, edescription, etime, edate):
        cursor = self.conn.cursor()
        query = "update experiment set ename = %s, edescription = %s, etime = %s, edate = %s where rid = %s \
                    and eid = %s;"
        cursor.execute(query, (ename, edescription, etime, edate, userid, experimentid,))
        self.conn.commit()
        return