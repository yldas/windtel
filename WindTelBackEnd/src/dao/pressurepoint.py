from config.dbconfig import pg_config
import psycopg2
from flask import jsonify

class PressurePointDAO:

    # def __init__(self):
    #     connection_url = "dbname=%s user=%s" % (pg_config['dbname'], pg_config['user'], pg_config['password'])
    #     self.conn = psycopg2.connect(connection_url)

    def getAllPressurePoints(self):
        result = []
        return result