import fetch from 'node-fetch';

import { domainPath, headers } from './commons';

const usersPath = `${domainPath}/users`


export const fetchUsers = async () => {
    return fetch(usersPath, {
        method: 'GET'
    }).then((resp) => {
        return resp.json()
    }).then((data) => {
        return data
    })
}

export const getUser = async (login) => {
    return fetch(`${usersPath}/${login}`, {
        method: 'GET',
        headers: headers
    }).then((resp) => {
        return resp.json()
    }).then((data) => {
        return data
    })
}

export const createUser = async (login) => {
    return fetch(`${usersPath}`, {
        method: 'POST',
        body: JSON.stringify({ "login": login }),
        headers: { 'Content-Type': 'application/json' }
    }).then((resp) => {
        return resp.json()
    }).then((data) => {
        return data
    })
}