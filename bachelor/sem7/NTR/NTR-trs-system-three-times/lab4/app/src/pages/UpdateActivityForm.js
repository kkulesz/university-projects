import React, { useState } from 'react'

import { Link, useLocation, useNavigate } from 'react-router-dom';

import { updateActivity } from '../dataSource/activitiesApi';

const UpdateActivityForm = () => {
    const navigate = useNavigate();
    const location = useLocation()
    const activity = location.state.activity
    const [inputs, setInputs] = useState(
        {
            code: activity.code, project: activity.project,
            budget: activity.budget, description: activity.description,
            year: activity.year, month: activity.month, day: activity.day
        }
    )
    const handleChange = (e) => {
        const name = e.target.name;
        const value = e.target.value;
        setInputs((values) => ({ ...values, [name]: value }));
    }
    const handleSubmit = async () => {
        await updateActivity(activity.owner, inputs.code, inputs.project, inputs.budget,
            inputs.description, inputs.year, inputs.month, inputs.day)
            .then()
        setTimeout(() => navigate('/activitiesDashboard'), 400)
        // navigate('/activitiesDashboard')
    }


    return (
        <div>
            <form >
                {/* <label>
                    Code:
                    <input type="text" name="code" onChange={handleChange} />
                </label> */}
                {/* <label>
                    <select name="project" onChange={handleChange}>
                        {projectNames.map((p) =>
                            <option key={p} value={p}>{p}</option>)}
                    </select>
                </label> */}
                <label>
                    Budget:
                    <input type="number" value={inputs.budget} name="budget" onChange={handleChange} />
                </label>
                <label>
                    Description:
                    <input type="text" value={inputs.description} name="description" onChange={handleChange} />
                </label>
                <div>
                    <input type="button" value="Update" onClick={handleSubmit} />
                </div>
            </form>
            <Link to="/activitiesDashboard" >
                Back
            </Link>
        </div>
    )

}

export default UpdateActivityForm;
