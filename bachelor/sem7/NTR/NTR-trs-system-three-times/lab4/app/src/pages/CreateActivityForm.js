import React, { useEffect, useState } from 'react'

import { Link, useNavigate } from 'react-router-dom';

import { createActivity } from '../dataSource/activitiesApi';
import { fetchActiveProjects } from '../dataSource/projectsApi'
import { useGlobalState } from '../state'

const CreateActivityForm = () => {
    const navigate = useNavigate();

    const { loggedUser, chosenDay, chosenMonth, chosenYear } = useGlobalState()
    const [projects, setProjects] = useState([])
    useEffect(() => {
        fetchActiveProjects()
            .then((res) => { setProjects(res) })
    }, [])
    const projectNames = projects.map(p => p.name)

    const [inputs, setInputs] = useState(
        {
            code: '', project: projectNames[0], budget: 0, description: '',
            year: chosenYear, month: chosenMonth, day: chosenDay
        }
    )
    const handleChange = (e) => {
        const name = e.target.name;
        const value = e.target.value;
        setInputs((values) => ({ ...values, [name]: value }));
    }
    const handleSubmit = async () => {
        await createActivity(loggedUser, inputs.code, inputs.project, inputs.budget,
            inputs.description, inputs.year, inputs.month, inputs.day).then()
        setTimeout(() => navigate('/activitiesDashboard'), 400)
        // navigate('/activitiesDashboard')
    }
    return (
        <div>
            <form>
                <label>
                    Code:
                    <input type="text" name="code" onChange={handleChange} />
                </label>
                <label>
                    <select name="project" onChange={handleChange}>
                        {projectNames.map((p) =>
                            <option key={p} value={p}>{p}</option>)}
                    </select>
                </label>
                <label>
                    Budget:
                    <input type="number" name="budget" onChange={handleChange} />
                </label>
                <label>
                    Description:
                    <input type="text" name="description" onChange={handleChange} />
                </label>
                <div>
                    <input type="button" value="Create" onClick={handleSubmit}/>
                </div>
            </form>
            <Link to="/activitiesDashboard">
                Back
            </Link>
            {projects.map((p) => <div>{p.owner} - {p.name}</div>)}
        </div>
    )

}

export default CreateActivityForm;
