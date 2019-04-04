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

    def getUserInformationById(self, userid):
        dao = ResearcherDAO()
        result = dao.getUserInformationById(userid)
        if result is None:
            return jsonify(Error="User doesn't exist!")
        else:
            result_map = self.build_researcher_dict(result)
        return jsonify(Users=result_map)

    def updateUserInformationById(self, userid, form):
        dao = ResearcherDAO()
        if not dao.getUserInformationById(userid):
            return jsonify(Error="User not found"), 404
        else:
            if len(form) != 8:
                return jsonify(Error="Malformed update request"), 400
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
                    response = dao.updateUserInformationById(userid, rname, rlast_name, remail, rpassword, rvocation, rdepartment, rinstitution, rcity)
                    result = self.build_researcher_attributes(userid, rname, rlast_name, remail, rpassword, rvocation, rdepartment, rinstitution, rcity)
                    return jsonify(Researcher=result), 200
                else:
                    return jsonify(Error="Unexpected attributes in update request"), 400

    def deleteUserById(self, userid):
        dao = ResearcherDAO()
        if not dao.getUserInformationById(userid):
            return jsonify(Error="User not found."), 404
        else:
            dao.deleteUserById(userid)
            return jsonify(DeleteStatus="OK"), 200

    def getAllExperimentsFromUserById(self, userid):
        dao = ResearcherDAO()
        experiments_list = dao.getAllExperimentsFromUserById(userid)
        result_map = []
        for row in experiments_list:
            result = self.build_experiment_dict(row)
            result_map.append(result)
        return jsonify(Experiments=result_map)

    def deleteAllExperimentsFromUserById(self, userid):
        dao = ResearcherDAO()
        if not dao.getUserInformationById(userid):
            return jsonify(Error="User not found."), 404
        elif not dao.getAllExperimentsFromUserById(userid):
            return jsonify(Error="No experiments found."), 404
        else:
            dao.deleteAllExperimentsFromUserById(userid)
            return jsonify(DeleteStatus="OK"), 200

    def getExperimentFromUserById(self, userid, experimentid):
        dao = ResearcherDAO()
        result = dao.getExperimentFromUserById(userid, experimentid)
        if result is None:
            return jsonify(Error="Experiment doesn't exist!")
        else:
            result_map = self.build_experiment_dict(result)
        return jsonify(Users=result_map)

    def deleteExperimentFromUserById(self, userid, experimentid):
        dao = ResearcherDAO()
        if not dao.getUserInformationById(userid):
            return jsonify(Error="User not found."), 404
        elif not dao.getAllExperimentsFromUserById(userid):
            return jsonify(Error="No experiments found."), 404
        else:
            dao.deleteExperimentFromUserById(userid, experimentid)
            return jsonify(DeleteStatus="OK"), 200

    def updateExperimentInformationById(self, userid, experimentid, form):
        dao = ResearcherDAO()
        if not dao.getAllExperimentsFromUserById(userid, experimentid):
            return jsonify(Error="Experiment not found"), 404
        else:
            if len(form) != 4:
                return jsonify(Error="Malformed update request"), 400
            else:
                ename = form['ename']
                edescription = form['edescription']
                etime = form['etime']
                edate = form['edate']
                if ename and edescription and etime and edate:
                    response = dao.updateExperimentInformationById(userid, experimentid)
                    result = self.build_experiment_attributes(experimentid, ename, edescription, etime, edate)
                    return jsonify(Experiment=result), 200
                else:
                    return jsonify(Error="Unexpected attributes in update request"), 400