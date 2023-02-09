import fetch from 'node-fetch';

import { domainPath, headers } from './commons';

const projectsPath = `${domainPath}/projects`

export const fetchActiveProjects = async () => {
    return fetch(projectsPath, {
        method: 'GET',
        headers: headers
    }).then((resp) => {
        return resp.json()
    }).then((data) => {
        return data
    })
}


