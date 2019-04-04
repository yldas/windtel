from config.dbconfig import pg_config
import psycopg2
from flask import jsonify

class ResearcherDAO:

    # def __init__(self):
    #     connection_url = "dbname=%s user=%s" % (pg_config['dbname'], pg_config['user'], pg_config['password'])
    #     self.conn = psycopg2.connect(connection_url)

    def registerResearcher(self, rname, rlast_name, remail, rpassword, rvocation, rdepartment, rinstitution, rcity):
        if rname == 'Kahlil':
            return 1
        elif rname == 'Nelson':
            return 2
        elif rname == 'Luis':
            return 3
        elif rname == 'Misael':
            return 4
        else:
            return 5

    def loginResearcher(self, remail, rpassword):
        if remail == 'kahlil.fonseca@upr.edu':
            return [1, 'Kahlil', 'Fonseca', remail, 'playstation123', 'Student', 'ICOM', 'UPRM', 'Cabo Rojo']
        else:
            return []

    def getAllUsers(self):
        result = []
        return result