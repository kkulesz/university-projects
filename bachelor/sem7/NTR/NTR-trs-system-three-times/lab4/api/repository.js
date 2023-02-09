class Repository {
    constructor() {
        this._fs = require('fs')

        this._dataDir = './data'
        this._usersFilename = `${this._dataDir}/users.json`
        this._projectsFilename = `${this._dataDir}/projects.json`
        this._activitiesFilename = `${this._dataDir}/activities.json`

        this._makeSureEverythingExists()
    }

    /*****      USERS      *****/
    createUser(newUser) {
        const users = this.getUsers()
        if (users.find(u => u.login === newUser.login)) {
            return undefined
        } else {
            users.push(newUser)
            this._saveUsers(users)
            return newUser
        }
    }

    getUsers() {
        return this._getUsers()
    }

    getUser(login) {
        const users = this._getUsers()
        return users.find(u => u.login == login)
    }

    /*****      ACTIVITES      *****/
    getActivities(login, year, month, day) {
        const allActivites = this._getActivities()
        return allActivites.filter(
            act => act.owner == login &&
                act.year == year &&
                act.month == month &&
                act.day == day)
    }

    getActivity(login, code) {
        const users = this.getUsers()
        return users.find(u => u.login === login)
    }

    createActivity(newActivity) {
        const allActivites = this._getActivities()
        allActivites.push(newActivity)
        this._saveActivities(allActivites)
        return newActivity
    }

    deleteActivity(login, code) {
        const allActivites = this._getActivities()
        const filtered = allActivites.filter(act => !(act.owner === login && act.code === code))
        if (filtered.length == allActivites) {
            return false
        } else {
            this._saveActivities(filtered.length > 0 ? filtered : [])
            return true
        }

    }

    updateActivity(login, updatedActivity) {
        const allActivites = this._getActivities()
        let found = false
        const updated = allActivites.map(act => {
            if (act.owner === login && act.code === updatedActivity.code) {
                found = true
                return updatedActivity
            } else {
                return act
            }
        })
        this._saveActivities(updated)
        return found
    }


    /*****      PROJECTS      *****/
    getProjects() {
        return this._getProjects()
    }



    /******************************************
     *****************PRIVATE******************
     ******************************************/

    _makeSureEverythingExists() {
        if (!this._fs.existsSync(this._dataDir)) {
            this._fs.mkdirSync(this._dataDir);
        }
        this._makeSureFileExists(this._usersFilename)
        this._makeSureFileExists(this._projectsFilename)
        this._makeSureFileExists(this._activitiesFilename)
    }

    _makeSureFileExists(filename) {
        if (!this._fs.existsSync(filename)) {
            this._fs.writeFile(filename, JSON.stringify([]), () => { })
        }
    }

    // users
    _saveUsers(users) { this._writeToFile(this._usersFilename, users) }
    _getUsers() { return this._readFromFile(this._usersFilename) }

    //projects
    _saveProjects(projects) { this._writeToFile(this._projectsFilename, projects) }
    _getProjects() { return this._readFromFile(this._projectsFilename) }

    //activities
    _saveActivities(activities) { this._writeToFile(this._activitiesFilename, activities) }
    _getActivities() { return this._readFromFile(this._activitiesFilename) }

    // general
    _writeToFile(filename, objects) {
        this._fs.writeFile(
            filename,
            JSON.stringify(objects, null, 2),
            () => { }
        )
    }

    _readFromFile(filename) {
        try {
            return JSON.parse(this._fs.readFileSync(filename, 'utf8'))
        } catch {
            return []
        }
    }
}

module.exports = Repository