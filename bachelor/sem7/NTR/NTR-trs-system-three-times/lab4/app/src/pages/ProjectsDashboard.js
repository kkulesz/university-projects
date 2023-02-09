import React, { useEffect, useState } from 'react'

import { fetchActiveProjects } from '../dataSource/projectsApi'

const ProjectsDashBoard = () => {
    const [projects, setProjects] = useState([])
    useEffect(() => {
        fetchActiveProjects()
            .then((res) => { setProjects(res) })
    }, [])

    console.log(projects)
    return (
        <div>
            {projects.map(
                p => { return <div>owner={p.owner}, project={p.name}, acceptedBudget={p.acceptedBudget}</div> }
            )}
        </div>
    )

}

export default ProjectsDashBoard;
