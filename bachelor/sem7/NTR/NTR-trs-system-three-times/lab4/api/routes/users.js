const Repository = require('../repository')

const express = require('express')
const router = express.Router()
const bodyParser = require('body-parser');
router.use(bodyParser.json());


const repo = new Repository()

router
    .route('/')
    .post((req, res) => {
        const result = repo.createUser(req.body)
        result ? res.send(result) : res.send(409) // conflict
    })
    .get((req, res) => {
        res.send(repo.getUsers())
    })

router.get('/:login', (req, res) => {
    const result = repo.getUser(req.params.login)
    result ? res.send(result) : res.send(404) // not found
})

module.exports = router
