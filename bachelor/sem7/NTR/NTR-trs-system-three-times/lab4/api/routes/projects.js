const Repository = require('../repository')

const express = require('express')
const router = express.Router()
const bodyParser = require('body-parser');
router.use(bodyParser.json());

const repo = new Repository()

router
    .route('/')
    // .post((req, res) => {
    //     res.send('project created')
    // })
    .get((req, res) => {
        res.send(repo.getProjects())
    })

module.exports = router