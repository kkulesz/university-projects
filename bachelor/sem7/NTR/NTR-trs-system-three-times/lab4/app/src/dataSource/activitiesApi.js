import fetch from 'node-fetch';

import { domainPath, headers } from './commons';

const activitiesPath = `${domainPath}/activities`

export const fetchActivitiesForDay = async (year, month, day, user) => {
    return fetch(`${activitiesPath}?user=${user}&year=${year}&month=${month}&day=${day}`, {
        method: 'GET',
        headers: headers
    }).then((resp) => {
        return resp.json()
    }).then((data) => {
        return data
    })
}

export const deleteActivity = async (code, user) => {
    return fetch(`${activitiesPath}?user=${user}&code=${code}`, {
        method: 'DELETE'
    }).then(() => { })
}

export const createActivity = async (user, code, project, budget, description, year, month, day) => {
    return fetch(activitiesPath, {
        method: 'POST',
        body: JSON.stringify(
            {
                "owner": user, "code": code, "project": project,
                "budget": budget, "description": description,
                "year": year, "month": month, "day": day
            }
        ),
        headers: { 'Content-Type': 'application/json' }
    }).then((resp) => {
        return resp.json()
    }).then((data) => {
        return data
    })
}

export const updateActivity = async (user, code, project, budget, description, year, month, day) => {
    return fetch(activitiesPath, {
        method: 'PUT',
        body: JSON.stringify(
            {
                "owner": user, "code": code, "project": project,
                "budget": budget, "description": description,
                "year": year, "month": month, "day": day
            }
        ),
        headers: { 'Content-Type': 'application/json' }
    }).then((resp) => {
        return resp.json()
    }).then((data) => {
        return data
    })
}