const Repository = require('../repository')

const express = require('express')
const router = express.Router()
const bodyParser = require('body-parser');
router.use(bodyParser.json());


const repo = new Repository()

router
    .route('/')
    .get((req, res) => {
        const queryParams = req.query
        const user = queryParams.user
        const year = queryParams.year
        const month = queryParams.month
        const day = queryParams.day
        res.send(repo.getActivities(user, year, month, day))
    })
    .post((req, res) => {
        res.send(repo.createActivity(req.body))
    })
    .delete((req, res) => {
        const queryParams = req.query
        const user = queryParams.user
        const code = queryParams.code
        repo.deleteActivity(user, code) ? res.sendStatus(200) : res.sendStatus(404) //not found
    })
    .put((req, res) => {
        const user = req.body.owner //TODO in authorization
        repo.updateActivity(user, req.body) ? res.send(req.body) : res.sendStatus(404)
    })


module.exports = router