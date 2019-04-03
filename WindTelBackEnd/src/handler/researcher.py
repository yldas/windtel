from flask import jsonify
from dao.researcher import ResearcherDAO

class ResearcherHandler:

    def build_researcher_dict(self, row):
        result = {}
        result['rid'] = row[0]
        result['rname'] = row[1]
        result['rlast_name'] = row[2]
        result['remail'] = row[3]
        result['rpassword'] = row[4]
        result['rvocation'] = row[5]
        result['rdepartment'] = row[6]
        result['rinstitution'] = row[7]
        result['rcity'] = row[8]
        return result

    def build_researcher_attributes(self, rid, rname, rlast_name, remail, rpassword, rvocation, rdepartment, rinstitution, rcity):
        result = {}
        result['rid'] = rid
        result['rname'] = rname
        result['rlast_name'] = rlast_name
        result['remail'] = remail
        result['rpassword'] = rpassword
        result['rvocation'] = rvocation
        result['rdepartment'] = rdepartment
        result['rinstitution'] = rinstitution
        result['rcity'] = rcity
        return result

    def registerResearcher(self, form):
        if len(form) != 8:
            return jsonify(Error="Malformed Post Request"), 400
        else:
            rname = form['rname']
            rlast_name = form['rlast_name']
            remail = form['remail']
            rpassword = form['rpassword']
            rvocation = form['rvocation']
            rdepartment = form['rdepartment']
            rinstitution = form['rinstitution']
            rcity = form['rcity']
            if rname and rlast_name and remail and rpassword and rvocation and rdepartment and rinstitution and rcity:
                dao = ResearcherDAO()
                rid = dao.registerResearcher(rname, rlast_name, remail, rpassword, rvocation, rdepartment, rinstitution, rcity)
                result = self.build_researcher_attributes(rid, rname, rlast_name, remail, rpassword, rvocation, rdepartment, rinstitution, rcity)
                return jsonify(User=result), 201
            else:
                return jsonify(Error="Malformed Post Request"), 400

    def loginResearcher(self, form):
        if len(form) != 2:
            return jsonify(Error="Malformed Post Request"), 400
        else:
            remail = form['remail']
            rpassword = form['rpassword']
            if remail and rpassword:
                dao = ResearcherDAO()
                result = dao.loginResearcher(remail, rpassword)
                dict_map = self.build_researcher_dict(result)
                return jsonify(User=dict_map)
            else:
                return jsonify(Error="Invalid email or password")

    def getAllUsers(self):
        dao = ResearcherDAO()
        user_list = dao.getAllUsers()
        result_map = []
        for row in user_list:
            result = self.build_researcher_dict(row)
            result_map.append(result)
        return jsonify(Users=result_map)